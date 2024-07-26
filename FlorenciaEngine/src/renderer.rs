use std::collections::HashMap;

use super::Result;
use ash::{
	self,
	ext,
	khr,
	vk
};
use raw_window_handle::{HasDisplayHandle, HasWindowHandle};
use winit::{
	application::ApplicationHandler,
	dpi,
	event::WindowEvent,
	event_loop::{ ActiveEventLoop, EventLoop },
	window::{ Window, WindowAttributes, WindowId },
};

struct Application {
	entry: ash::Entry,
	instance: ash::Instance,
	physicalDevice: vk::PhysicalDevice,
	logicalDevice: ash::Device,
	graphicsQueue: vk::Queue,
	presentQueue: vk::Queue,
	swapchainFormat: vk::Format,
	swapchainInstance: khr::swapchain::Instance,
	swapchainDevice: khr::swapchain::Device,
	swapchainExtent: vk::Extent2D,
	swapchain: vk::SwapchainKHR,
	swapchainImages: Vec<vk::Image>,
	swapchainImageViews: Vec<vk::ImageView>,
	swapchainFrameBuffers: Vec<vk::Framebuffer>,
	recreateSwapchain: bool,
	renderPass: vk::RenderPass,
	pipelineLayout: vk::PipelineLayout,
	graphicsPipeline: vk::Pipeline,
	commandPool: vk::CommandPool,
	commandBuffers: Vec<vk::CommandBuffer>,
	imageAvailableSemaphores: Vec<vk::Semaphore>,
	renderFinishedSemaphores: Vec<vk::Semaphore>,
	inFlightFences: Vec<vk::Fence>,
	currentFrame: usize,

	surfaceInstance: khr::surface::Instance,
	surface: vk::SurfaceKHR,

	debugInstance: ext::debug_utils::Instance,
	debugMessenger: vk::DebugUtilsMessengerEXT,

	windows: HashMap<WindowId, Window>,
}

#[derive(Default)]
struct QueueFamilyIndices {
	graphicsFamily: Option<usize>,
	presentFamily: Option<usize>,
}

impl QueueFamilyIndices {
	pub fn complete(&self) -> bool {
		self.graphicsFamily.is_some() && self.presentFamily.is_some()
	}
}

impl Application {
	const VALIDATION: bool = true;
	const VALIDATION_LAYERS: [*const std::ffi::c_char; 1] = [
		c"VK_LAYER_KHRONOS_validation".as_ptr(),
	];
	const DEVICE_EXTENSIONS: [*const std::ffi::c_char; 1] = [
		khr::swapchain::NAME.as_ptr(),
	];
	const MAX_FRAMES_IN_FLIGHT: usize = 2;
	fn createWindow((width, height): (u32, u32), title: &str, eventLoop: &EventLoop<()>) -> Result<(HashMap<WindowId, Window>, WindowId)> {
		let mut windows = HashMap::new();
		let windowAttributes = WindowAttributes::default()
			.with_title(title)
			.with_inner_size(dpi::LogicalSize::new(width, height))
			.with_visible(true)
			.with_resizable(true)
			.with_window_icon(None);
		// if let Some(token) = eventLoop.read_token_from_env() {
		// 	startup_notify::reset_activation_token_env();
		// 	windowAttributes = windowAttributes.with_activation_token(token);
		// }
		let window = eventLoop.create_window(windowAttributes)?;
		let windowID = window.id();

		windows.insert(windowID, window);
		Ok((windows, windowID))
	}
	fn getRequiredExtensions(eventLoop: &EventLoop<()>) -> Result<Vec<*const std::ffi::c_char>> {
		let windowExtensions = ash_window::enumerate_required_extensions(eventLoop.display_handle()?.into())?;
		let mut requiredExtensions = Vec::with_capacity(windowExtensions.len() + 1);
		for extension in windowExtensions {
			requiredExtensions.push(*extension);
		}
		requiredExtensions.push(ext::debug_utils::NAME.as_ptr());
		Ok(requiredExtensions)
	}
	fn createDebugCreateInfo(_entry: &ash::Entry) -> vk::DebugUtilsMessengerCreateInfoEXT {
		extern "system" fn vulkanDebugUtilsCallback(messageSeverity: vk::DebugUtilsMessageSeverityFlagsEXT, messageType: vk::DebugUtilsMessageTypeFlagsEXT, pCallbackData: *const vk::DebugUtilsMessengerCallbackDataEXT, pUserData: *mut std::ffi::c_void) -> vk::Bool32 {
			let (severity, color) = match messageSeverity {
				vk::DebugUtilsMessageSeverityFlagsEXT::VERBOSE => ("Verbose", (199, 0, 240)),
				vk::DebugUtilsMessageSeverityFlagsEXT::WARNING => ("Warning", (255, 255, 0)),
				vk::DebugUtilsMessageSeverityFlagsEXT::ERROR => ("Error", (255, 50, 0)),
				vk::DebugUtilsMessageSeverityFlagsEXT::INFO => ("Info", (100, 200, 0)),
				_ => ("Unknown", (255u8, 255u8, 255u8)),
			};
			let types = match messageType {
				vk::DebugUtilsMessageTypeFlagsEXT::GENERAL => "General",
				vk::DebugUtilsMessageTypeFlagsEXT::PERFORMANCE => "Performance",
				vk::DebugUtilsMessageTypeFlagsEXT::VALIDATION => "Validation",
				_ => "Unknown",
			};
			let _ = pUserData;
			let message = unsafe { std::ffi::CStr::from_ptr((*pCallbackData).p_message) };
			println!("[Debug][{}][{}]: \x1b[38;2;{};{};{}m{:?}\x1B[0m", severity, types, color.0, color.1, color.2, message);

			vk::FALSE
		}
		vk::DebugUtilsMessengerCreateInfoEXT::default()
			.flags(vk::DebugUtilsMessengerCreateFlagsEXT::empty())
			.message_severity(vk::DebugUtilsMessageSeverityFlagsEXT::VERBOSE | vk::DebugUtilsMessageSeverityFlagsEXT::WARNING | vk::DebugUtilsMessageSeverityFlagsEXT::ERROR /* | vk::DebugUtilsMessageSeverityFlagsEXT::INFO */)
			.message_type(vk::DebugUtilsMessageTypeFlagsEXT::GENERAL | vk::DebugUtilsMessageTypeFlagsEXT::VALIDATION | vk::DebugUtilsMessageTypeFlagsEXT::PERFORMANCE /* | vk::DebugUtilsMessageTypeFlagsEXT::DEVICE_ADDRESS_BINDING */)
			.pfn_user_callback(Some(vulkanDebugUtilsCallback))
	}
	fn checkValidationLayerSupport(entry: &ash::Entry) -> bool {
		let layerProperties = unsafe { entry.enumerate_instance_layer_properties() }.unwrap();
		for layerName in Self::VALIDATION_LAYERS {
			let mut found = false;
			for properties in &layerProperties {
				let layerName = unsafe { std::ffi::CStr::from_ptr(layerName) };
				if layerName == properties.layer_name_as_c_str().unwrap() {
					found = true;
					break;
				}
			}
			if !found {
				return false;
			}
		}
		true
	}
	fn checkDeviceExtensionSupport(instance: &ash::Instance, physicalDevice: vk::PhysicalDevice) -> bool {
		let extensionProperties = unsafe { instance.enumerate_device_extension_properties(physicalDevice) }.unwrap();
		for deviceExtensions in Self::DEVICE_EXTENSIONS {
			let mut found = false;
			for properties in &extensionProperties {
				let extensionName = unsafe { std::ffi::CStr::from_ptr(deviceExtensions) };
				if extensionName == properties.extension_name_as_c_str().unwrap() {
					found = true;
					break;
				}
			}
			if !found {
				return false;
			}
		}
		true
	}
	fn createInstance(entry: &ash::Entry, eventLoop: &EventLoop<()>) -> Result<ash::Instance> {
		if Self::VALIDATION && !Self::checkValidationLayerSupport(entry) {
			println!("No Validation");
		}
		let applicationInfo = vk::ApplicationInfo::default()
			.application_name(c"App Name")
			.application_version(vk::make_api_version(0, 0, 0, 0))
			.engine_name(c"Engine Name")
			.engine_version(vk::make_api_version(0, 0, 0, 0))
			.api_version(vk::API_VERSION_1_3);
		let requiredExtensions = Self::getRequiredExtensions(eventLoop)?;

		Ok(match Self::VALIDATION {
			true => {
				let mut debugCreateInfo = Self::createDebugCreateInfo(entry);
				let instanceCreateInfo = vk::InstanceCreateInfo::default()
					.push_next(&mut debugCreateInfo)
					.application_info(&applicationInfo)
					.enabled_extension_names(&requiredExtensions)
					.enabled_layer_names(&Self::VALIDATION_LAYERS);
				unsafe { entry.create_instance(&instanceCreateInfo, None) }?
			},
			false => {
				let instanceCreateInfo = vk::InstanceCreateInfo::default()
					.application_info(&applicationInfo)
					.enabled_extension_names(&requiredExtensions);
				unsafe { entry.create_instance(&instanceCreateInfo, None) }?
			},
		})
	}
	fn setupDebugMessenger(entry: &ash::Entry, instance: &ash::Instance) -> Result<(ext::debug_utils::Instance, vk::DebugUtilsMessengerEXT)> {
		let debugLoader = ext::debug_utils::Instance::new(entry, instance);
		let createInfo = Self::createDebugCreateInfo(entry);
		let messenger = match Self::VALIDATION {
			true => { unsafe { debugLoader.create_debug_utils_messenger(&createInfo, None) }? },
			false => { vk::DebugUtilsMessengerEXT::null() },
		};
		Ok((debugLoader, messenger))
	}
	fn findQueueFamilies(instance: &ash::Instance, surfaceInstance: &khr::surface::Instance, surface: vk::SurfaceKHR, physicalDevice: vk::PhysicalDevice) -> QueueFamilyIndices {
		let mut indices = QueueFamilyIndices::default();
		let queueFamilyProperties = unsafe { instance.get_physical_device_queue_family_properties(physicalDevice) };
		for (i, queueFamily) in queueFamilyProperties.iter().enumerate() {
			if queueFamily.queue_flags.contains(vk::QueueFlags::GRAPHICS) {
				indices.graphicsFamily = Some(i);
			}
			if unsafe { surfaceInstance.get_physical_device_surface_support(physicalDevice, i as u32, surface) }.unwrap() {
				indices.presentFamily = Some(i);
			}

			if indices.complete() {
				break;
			}
		}
		indices
	}
	fn querySwapchainSupport(surfaceInstance: &khr::surface::Instance, surface: vk::SurfaceKHR, physicalDevice: vk::PhysicalDevice) -> Result<(vk::SurfaceCapabilitiesKHR, Vec<vk::SurfaceFormatKHR>, Vec<vk::PresentModeKHR>)> {
		let surfaceCapabilities = unsafe { surfaceInstance.get_physical_device_surface_capabilities(physicalDevice, surface) }?;
		let formats = unsafe { surfaceInstance.get_physical_device_surface_formats(physicalDevice, surface) }?;
		let presentModes = unsafe { surfaceInstance.get_physical_device_surface_present_modes(physicalDevice, surface) }?;
		Ok((surfaceCapabilities, formats, presentModes))
	}
	fn physicalDeviceSuitable(instance: &ash::Instance, surfaceInstance: &khr::surface::Instance, surface: vk::SurfaceKHR, physicalDevice: vk::PhysicalDevice) -> bool {
		// let properties = unsafe { instance.get_physical_device_properties(physicalDevice) };
		// let features = unsafe { instance.get_physical_device_features(physicalDevice) };
		// properties.device_type == vk::PhysicalDeviceType::DISCRETE_GPU && features.geometry_shader == vk::TRUE
		let indices = Self::findQueueFamilies(instance, surfaceInstance, surface, physicalDevice);
		let swapchainAdequate = if Self::checkDeviceExtensionSupport(instance, physicalDevice) {
			let (_capabilities, formats, presentModes) = Self::querySwapchainSupport(surfaceInstance, surface, physicalDevice).unwrap();
			!formats.is_empty() && !presentModes.is_empty()
		} else { false };
		indices.complete() && Self::checkDeviceExtensionSupport(instance, physicalDevice) && swapchainAdequate
	}
	fn pickPhysicalDevice(instance: &ash::Instance, surfaceInstance: &khr::surface::Instance, surface: vk::SurfaceKHR) -> Result<vk::PhysicalDevice> {
		let mut result = Err(vk::Result::ERROR_FEATURE_NOT_PRESENT);
		for physicalDevice in unsafe { instance.enumerate_physical_devices() }? {
			if Self::physicalDeviceSuitable(instance, surfaceInstance, surface, physicalDevice) {
				result = Ok(physicalDevice);
				break;
			}
		}
		Ok(result?)
	}
	fn createLogicalDevice(instance: &ash::Instance, surfaceInstance: &khr::surface::Instance, surface: vk::SurfaceKHR, physicalDevice: vk::PhysicalDevice) -> Result<(ash::Device, vk::Queue, vk::Queue)> {
		let indices = Self::findQueueFamilies(instance, surfaceInstance, surface, physicalDevice);

		let deviceQueuePriorities = [
			1.0,
		];
		let uniqueQueueFamilies = {
			let mut uniqueQueueFamilies = std::collections::BTreeSet::new();
			uniqueQueueFamilies.insert(indices.graphicsFamily.unwrap());
			uniqueQueueFamilies.insert(indices.presentFamily.unwrap());
			uniqueQueueFamilies
		};
		let deviceQueueCreateInfos = {
			let mut deviceQueueCreateInfos = Vec::new();
			for queueFamily in uniqueQueueFamilies {
				deviceQueueCreateInfos.push(vk::DeviceQueueCreateInfo::default()
					.queue_family_index(queueFamily as u32)
					.queue_priorities(&deviceQueuePriorities))
			}
			deviceQueueCreateInfos
		};
		let mut dynamicRenderingFeatures = vk::PhysicalDeviceDynamicRenderingFeatures::default()
			.dynamic_rendering(true);
		let mut physicalDeviceSynchronization2Features = vk::PhysicalDeviceSynchronization2Features::default()
			.synchronization2(true);
		let mut physicalDeviceFeatures2 = vk::PhysicalDeviceFeatures2::default()
			.push_next(&mut physicalDeviceSynchronization2Features);
		let deviceCreateInfo = if Self::VALIDATION {
			vk::DeviceCreateInfo::default()
				.enabled_layer_names(&Self::VALIDATION_LAYERS)
		} else {
			vk::DeviceCreateInfo::default()
		}.queue_create_infos(&deviceQueueCreateInfos)
		.enabled_extension_names(&Self::DEVICE_EXTENSIONS)
		.push_next(&mut dynamicRenderingFeatures)
		.push_next(&mut physicalDeviceFeatures2);
		let logicalDevice = unsafe { instance.create_device(physicalDevice, &deviceCreateInfo, None) }?;
		let graphicsQueue = unsafe { logicalDevice.get_device_queue(indices.graphicsFamily.unwrap() as u32, 0) };
		let presentQueue = unsafe { logicalDevice.get_device_queue(indices.presentFamily.unwrap() as u32, 0) };
		Ok((logicalDevice, graphicsQueue, presentQueue))
	}
	fn chooseSwapSurfaceFormat(availableFormats: &Vec<vk::SurfaceFormatKHR>) -> Option<vk::SurfaceFormatKHR> {
		for format in availableFormats {
			if format.format == vk::Format::B8G8R8A8_SRGB && format.color_space == vk::ColorSpaceKHR::SRGB_NONLINEAR {
				return Some(*format);
			}
		}
		availableFormats.first().copied()
	}
	fn chooseSwapPresentMode(availableModes: &Vec<vk::PresentModeKHR>) -> vk::PresentModeKHR {
		for mode in availableModes {
			if *mode == vk::PresentModeKHR::MAILBOX {
				return *mode;
			}
		}
		vk::PresentModeKHR::FIFO
	}
	fn chooseSwapExtent(window: &Window, capabilities: &vk::SurfaceCapabilitiesKHR) -> vk::Extent2D {
		if capabilities.current_extent.width != u32::MAX {
			capabilities.current_extent
		} else {
			let dpi::PhysicalSize { width, height } = window.inner_size();
			vk::Extent2D::default()
				.width(width.clamp(capabilities.min_image_extent.width, capabilities.max_image_extent.width))
				.height(height.clamp(capabilities.min_image_extent.height, capabilities.max_image_extent.height))
		}
	}
	fn createSurface(entry: &ash::Entry, instance: &ash::Instance, window: &Window) -> Result<vk::SurfaceKHR> {
		Ok(unsafe { ash_window::create_surface(entry, instance, window.display_handle()?.into(), window.window_handle()?.into(), None) }?)
	}
	fn createSwapchain(entry: &ash::Entry, instance: &ash::Instance, window: &Window, surfaceInstance: &khr::surface::Instance, surface: vk::SurfaceKHR, physicalDevice: vk::PhysicalDevice, logicalDevice: &ash::Device) -> Result<(khr::swapchain::Instance, khr::swapchain::Device, vk::Format, vk::Extent2D, vk::SwapchainKHR, Vec<vk::Image>)> {
		let (capabilities, formats, presentModes) = Self::querySwapchainSupport(surfaceInstance, surface, physicalDevice)?;
		let surfaceFormat = Self::chooseSwapSurfaceFormat(&formats).unwrap();
		let presentMode = Self::chooseSwapPresentMode(&presentModes);
		let swapchainExtent = Self::chooseSwapExtent(window, &capabilities);
		let indices = Self::findQueueFamilies(instance, surfaceInstance, surface, physicalDevice);
		let imageCount = if capabilities.max_image_count > 0 && capabilities.min_image_count + 1 > capabilities.max_image_count {
			capabilities.max_image_count
		} else {
			capabilities.min_image_count + 1
		};
		let queueFamilyIndices = [
			indices.graphicsFamily.unwrap() as u32,
			indices.presentFamily.unwrap() as u32,
		];
		let swapchainInstance = khr::swapchain::Instance::new(entry, instance);
		let swapchainDevice = khr::swapchain::Device::new(instance, logicalDevice);
		let swapchainCreateInfo = if indices.graphicsFamily != indices.presentFamily {
			vk::SwapchainCreateInfoKHR::default().image_sharing_mode(vk::SharingMode::CONCURRENT)
				.queue_family_indices(&queueFamilyIndices)
		} else {
			vk::SwapchainCreateInfoKHR::default().image_sharing_mode(vk::SharingMode::EXCLUSIVE)
		}.surface(surface)
		.min_image_count(imageCount)
		.image_format(surfaceFormat.format)
		.image_color_space(surfaceFormat.color_space)
		.image_extent(swapchainExtent)
		.image_array_layers(1)
		.image_usage(vk::ImageUsageFlags::COLOR_ATTACHMENT)
		.pre_transform(capabilities.current_transform)
		.composite_alpha(vk::CompositeAlphaFlagsKHR::OPAQUE)
		.present_mode(presentMode)
		.clipped(true)
		.old_swapchain(vk::SwapchainKHR::null());
		let swapchain = unsafe { swapchainDevice.create_swapchain(&swapchainCreateInfo, None) }?;
		let swapchainImages = unsafe { swapchainDevice.get_swapchain_images(swapchain) }?;
		Ok((swapchainInstance, swapchainDevice, surfaceFormat.format, swapchainExtent, swapchain, swapchainImages))
	}
	fn createSwapchainImageViews(logicalDevice: &ash::Device, format: vk::Format, swapchainImages: &Vec<vk::Image>) -> Result<Vec<vk::ImageView>> {
		let mut swapchainImageViews = Vec::with_capacity(swapchainImages.len());
		for image in swapchainImages {
			let imageSubresourceRange = vk::ImageSubresourceRange::default()
				.aspect_mask(vk::ImageAspectFlags::COLOR)
				.base_mip_level(0)
				.level_count(1)
				.base_array_layer(0)
				.layer_count(1);
			let components = vk::ComponentMapping::default()
				.r(vk::ComponentSwizzle::IDENTITY)
				.g(vk::ComponentSwizzle::IDENTITY)
				.b(vk::ComponentSwizzle::IDENTITY)
				.a(vk::ComponentSwizzle::IDENTITY);
			let imageViewCreateInfo = vk::ImageViewCreateInfo::default()
				.image(*image)
				.view_type(vk::ImageViewType::TYPE_2D)
				.format(format)
				.components(components)
				.subresource_range(imageSubresourceRange);
			swapchainImageViews.push(unsafe { logicalDevice.create_image_view(&imageViewCreateInfo, None) }?);
		}
		Ok(swapchainImageViews)
	}
	fn createShaderModule(binary: &[u32], logicalDevice: &ash::Device) -> Result<vk::ShaderModule> {
		let shaderModuleCreateInfo = vk::ShaderModuleCreateInfo::default()
			.code(binary);
		Ok(unsafe { logicalDevice.create_shader_module(&shaderModuleCreateInfo, None) }?)
	}
	fn createRenderpass(logicalDevice: &ash::Device, swapchainFormat: vk::Format) -> Result<vk::RenderPass> {
		let colorAttachmentDescriptions = [
			vk::AttachmentDescription::default()
				.format(swapchainFormat)
				.samples(vk::SampleCountFlags::TYPE_1)
				.load_op(vk::AttachmentLoadOp::CLEAR)
				.store_op(vk::AttachmentStoreOp::STORE)
				.stencil_load_op(vk::AttachmentLoadOp::DONT_CARE)
				.stencil_store_op(vk::AttachmentStoreOp::DONT_CARE)
				.initial_layout(vk::ImageLayout::UNDEFINED)
				.final_layout(vk::ImageLayout::PRESENT_SRC_KHR),
		];
		let colorAttachmentReferences = [
			vk::AttachmentReference::default()
				.attachment(0)
				.layout(vk::ImageLayout::COLOR_ATTACHMENT_OPTIMAL),
		];
		let subpasses = [
			vk::SubpassDescription::default()
				.pipeline_bind_point(vk::PipelineBindPoint::GRAPHICS)
				.color_attachments(&colorAttachmentReferences),
		];
		let subpassDependencies = [
			vk::SubpassDependency::default()
				.src_subpass(vk::SUBPASS_EXTERNAL)
				.dst_subpass(0)
				.src_stage_mask(vk::PipelineStageFlags::COLOR_ATTACHMENT_OUTPUT)
				.src_access_mask(vk::AccessFlags::default())
				.dst_stage_mask(vk::PipelineStageFlags::COLOR_ATTACHMENT_OUTPUT)
				.dst_access_mask(vk::AccessFlags::COLOR_ATTACHMENT_WRITE),
		];
		let renderPassCreateInfo = vk::RenderPassCreateInfo::default()
			.attachments(&colorAttachmentDescriptions)
			.subpasses(&subpasses)
			.dependencies(&subpassDependencies);
		Ok(unsafe { logicalDevice.create_render_pass(&renderPassCreateInfo, None) }?)
	}
	fn createGraphicsPipeline(vertexBinary: &[u32], fragmentBinary: &[u32], logicalDevice: &ash::Device, renderPass: vk::RenderPass) -> Result<(vk::PipelineLayout, vk::Pipeline)> {
		let vertexShaderModule = Self::createShaderModule(vertexBinary, logicalDevice)?;
		let fragmentShaderModule = Self::createShaderModule(fragmentBinary, logicalDevice)?;
		let shaderStages = [
			vk::PipelineShaderStageCreateInfo::default()
				.stage(vk::ShaderStageFlags::VERTEX)
				.module(vertexShaderModule)
				.name(c"main"),
			vk::PipelineShaderStageCreateInfo::default()
				.stage(vk::ShaderStageFlags::FRAGMENT)
				.module(fragmentShaderModule)
				.name(c"main"),
		];
		let vertexBindingDescriptions = [
		];
		let vertexAttributeDescriptions = [
		];
		let vertexInputStateCreateInfo = vk::PipelineVertexInputStateCreateInfo::default()
			.vertex_binding_descriptions(&vertexBindingDescriptions)
			.vertex_attribute_descriptions(&vertexAttributeDescriptions);
		let inputAssemblyStateCreateInfo = vk::PipelineInputAssemblyStateCreateInfo::default()
			.topology(vk::PrimitiveTopology::TRIANGLE_LIST)
			.primitive_restart_enable(false);
		let viewportStateCreateInfo = vk::PipelineViewportStateCreateInfo::default()
			.viewport_count(1)
			.scissor_count(1);
		let rasterizationStateCreateInfo = vk::PipelineRasterizationStateCreateInfo::default()
			.depth_clamp_enable(false)
			.rasterizer_discard_enable(false)
			.polygon_mode(vk::PolygonMode::FILL)
			.line_width(1.0)
			.cull_mode(vk::CullModeFlags::BACK)
			.front_face(vk::FrontFace::CLOCKWISE)
			.depth_bias_enable(false)
			.depth_bias_constant_factor(0.0)
			.depth_bias_clamp(0.0)
			.depth_bias_slope_factor(0.0);
		let sampleMasks = [];
		let multisampleStateCreateInfo = vk::PipelineMultisampleStateCreateInfo::default()
			.sample_shading_enable(false)
			.rasterization_samples(vk::SampleCountFlags::TYPE_1)
			.min_sample_shading(1.0)
			.sample_mask(&sampleMasks)
			.alpha_to_coverage_enable(false)
			.alpha_to_one_enable(false)
		;
		let attachments = [
			vk::PipelineColorBlendAttachmentState::default()
				.color_write_mask(vk::ColorComponentFlags::RGBA)
				.blend_enable(false)
				.src_color_blend_factor(vk::BlendFactor::ONE)
				.dst_color_blend_factor(vk::BlendFactor::ZERO)
				.color_blend_op(vk::BlendOp::ADD)
				.src_alpha_blend_factor(vk::BlendFactor::ONE)
				.dst_alpha_blend_factor(vk::BlendFactor::ZERO)
				.alpha_blend_op(vk::BlendOp::ADD),
		];
		let colorBlendStateCreateInfo = vk::PipelineColorBlendStateCreateInfo::default()
			.logic_op_enable(false)
			.logic_op(vk::LogicOp::COPY)
			.attachments(&attachments)
			.blend_constants([0.0, 0.0, 0.0, 0.0]);
		let dynamicStates = [
			vk::DynamicState::VIEWPORT,
			vk::DynamicState::SCISSOR,
		];
		let dynamicStateCreateInfo = vk::PipelineDynamicStateCreateInfo::default()
			.dynamic_states(&dynamicStates);
		let pipelineLayouts = [];
		let pushConstantRanges = [];
		let pipelineLayoutCreateInfo = vk::PipelineLayoutCreateInfo::default()
			.set_layouts(&pipelineLayouts)
			.push_constant_ranges(&pushConstantRanges);
		let pipelineLayout = unsafe { logicalDevice.create_pipeline_layout(&pipelineLayoutCreateInfo, None) }?;
		let graphicsPipelineCreateInfos = [
			vk::GraphicsPipelineCreateInfo::default()
				.stages(&shaderStages)
				.vertex_input_state(&vertexInputStateCreateInfo)
				.input_assembly_state(&inputAssemblyStateCreateInfo)
				.viewport_state(&viewportStateCreateInfo)
				.rasterization_state(&rasterizationStateCreateInfo)
				.multisample_state(&multisampleStateCreateInfo)
				.color_blend_state(&colorBlendStateCreateInfo)
				.dynamic_state(&dynamicStateCreateInfo)
				.layout(pipelineLayout)
				.render_pass(renderPass)
				.subpass(0)
				.base_pipeline_handle(vk::Pipeline::null())
				.base_pipeline_index(-1),
		];
		let graphicsPipeline = match unsafe { logicalDevice.create_graphics_pipelines(vk::PipelineCache::null(), &graphicsPipelineCreateInfos, None) } {
			Ok(pipelines) => pipelines[0],
			Err((_, err)) => return Err(err.into()),
		};
		unsafe {
			logicalDevice.destroy_shader_module(vertexShaderModule, None);
			logicalDevice.destroy_shader_module(fragmentShaderModule, None);
		}
		Ok((pipelineLayout, graphicsPipeline))
	}
	fn createFrameBuffers(logicalDevice: &ash::Device, renderPass: vk::RenderPass, swapchainExtent: vk::Extent2D, swapchainImageViews: &Vec<vk::ImageView>) -> Result<Vec<vk::Framebuffer>> {
		let mut framebuffers = Vec::with_capacity(swapchainImageViews.len());
		for imageView in swapchainImageViews {
			let attachments = [
				*imageView
			];
			let frameBufferCreateInfo = vk::FramebufferCreateInfo::default()
				.render_pass(renderPass)
				.attachments(&attachments)
				.width(swapchainExtent.width)
				.height(swapchainExtent.height)
				.layers(1);
			framebuffers.push(unsafe { logicalDevice.create_framebuffer(&frameBufferCreateInfo, None) }?)
		}
		Ok(framebuffers)
	}
	fn createCommandPool(instance: &ash::Instance, logicalDevice: &ash::Device, surfaceInstance: &khr::surface::Instance, surface: vk::SurfaceKHR, physicalDevice: vk::PhysicalDevice) -> Result<vk::CommandPool> {
		let indices = Self::findQueueFamilies(instance, surfaceInstance, surface, physicalDevice);
		let commandPoolCreateInfo = vk::CommandPoolCreateInfo::default()
			.flags(vk::CommandPoolCreateFlags::RESET_COMMAND_BUFFER)
			.queue_family_index(indices.graphicsFamily.unwrap() as u32);
		Ok(unsafe { logicalDevice.create_command_pool(&commandPoolCreateInfo, None) }?)
	}
	fn createCommandBuffers(logicalDevice: &ash::Device, commandPool: vk::CommandPool) -> Result<Vec<vk::CommandBuffer>> {
		let commandBufferAllocateInfo = vk::CommandBufferAllocateInfo::default()
			.level(vk::CommandBufferLevel::PRIMARY)
			.command_pool(commandPool)
			.command_buffer_count(Self::MAX_FRAMES_IN_FLIGHT as u32);
		Ok(unsafe { logicalDevice.allocate_command_buffers(&commandBufferAllocateInfo) }?)
	}
	fn recordCommandBuffer(&self, commandBuffer: vk::CommandBuffer, imageIndex: usize) -> Result<()> {
		let commandBufferBeginInfo = vk::CommandBufferBeginInfo::default()
			.flags(vk::CommandBufferUsageFlags::default());
		let renderArea = vk::Rect2D::default()
			.offset(vk::Offset2D::default())
			.extent(self.swapchainExtent);
		let clearValues = [
			vk::ClearValue::default(),
		];
		let renderPassBeginInfo = vk::RenderPassBeginInfo::default()
			.render_pass(self.renderPass)
			.framebuffer(self.swapchainFrameBuffers[imageIndex])
			.render_area(renderArea)
			.clear_values(&clearValues);
		let viewports = [
			vk::Viewport::default()
				.x(0.0)
				.y(0.0)
				.width(self.swapchainExtent.width as f32)
				.height(self.swapchainExtent.height as f32)
				.min_depth(0.0)
				.max_depth(1.0),
		];
		let scissors = [
			vk::Rect2D::default()
				.offset(vk::Offset2D::default())
				.extent(self.swapchainExtent),
		];
		unsafe {
			self.logicalDevice.begin_command_buffer(commandBuffer, &commandBufferBeginInfo)?;
			self.logicalDevice.cmd_begin_render_pass(commandBuffer, &renderPassBeginInfo, vk::SubpassContents::INLINE);
			self.logicalDevice.cmd_bind_pipeline(commandBuffer, vk::PipelineBindPoint::GRAPHICS, self.graphicsPipeline);
			self.logicalDevice.cmd_set_viewport(commandBuffer, 0, &viewports);
			self.logicalDevice.cmd_set_scissor(commandBuffer, 0, &scissors);
			self.logicalDevice.cmd_draw(commandBuffer, 3, 1, 0, 0);
			self.logicalDevice.cmd_end_render_pass(commandBuffer);
			self.logicalDevice.end_command_buffer(commandBuffer)?;
		}
		Ok(())
	}
	fn createSyncObjects(logicalDevice: &ash::Device) -> Result<(Vec<vk::Semaphore>, Vec<vk::Semaphore>, Vec<vk::Fence>)> {
		let mut imageAvailableSemaphores = Vec::with_capacity(Self::MAX_FRAMES_IN_FLIGHT);
		let mut renderFinishedSemaphores = Vec::with_capacity(Self::MAX_FRAMES_IN_FLIGHT);
		let mut inFlightFences = Vec::with_capacity(Self::MAX_FRAMES_IN_FLIGHT);
		let semaphoreCreateInfo = vk::SemaphoreCreateInfo::default();
		let fenceCreateInfo = vk::FenceCreateInfo::default()
			.flags(vk::FenceCreateFlags::SIGNALED);
		for _i in 0..Self::MAX_FRAMES_IN_FLIGHT {
			imageAvailableSemaphores.push(unsafe { logicalDevice.create_semaphore(&semaphoreCreateInfo, None) }?);
			renderFinishedSemaphores.push(unsafe { logicalDevice.create_semaphore(&semaphoreCreateInfo, None) }?);
			inFlightFences.push(unsafe { logicalDevice.create_fence(&fenceCreateInfo, None) }?);
		}
		Ok((imageAvailableSemaphores, renderFinishedSemaphores, inFlightFences))
	}
	fn draw(&mut self) -> Result<()> {
		let inFlightFences = [
			self.inFlightFences[self.currentFrame],
		];
		unsafe {
			self.logicalDevice.wait_for_fences(&self.inFlightFences, true, u64::MAX)?;
			self.logicalDevice.reset_fences(&inFlightFences)?;
		};
		let (imageIndex, _suboptimal) = unsafe { self.swapchainDevice.acquire_next_image(self.swapchain, u64::MAX, self.imageAvailableSemaphores[self.currentFrame], vk::Fence::null()) }?;
		unsafe { self.logicalDevice.reset_command_buffer(self.commandBuffers[self.currentFrame], vk::CommandBufferResetFlags::default()) }?;
		self.recordCommandBuffer(self.commandBuffers[self.currentFrame], imageIndex as usize)?;
		let imageAvailableSemaphores = [
			self.imageAvailableSemaphores[self.currentFrame],
		];
		let renderFinishedSemaphores = [
			self.renderFinishedSemaphores[self.currentFrame],
		];
		let waitStages = [
			vk::PipelineStageFlags::COLOR_ATTACHMENT_OUTPUT,
		];
		let commandBuffers = [
			self.commandBuffers[self.currentFrame],
		];
		let submitInfos = [
			vk::SubmitInfo::default()
				.wait_semaphores(&imageAvailableSemaphores)
				.signal_semaphores(&renderFinishedSemaphores)
				.wait_dst_stage_mask(&waitStages)
				.command_buffers(&commandBuffers),
		];
		let swapchains = [
			self.swapchain,
		];
		let imageIndices = [
			imageIndex,
		];
		unsafe { self.logicalDevice.queue_submit(self.graphicsQueue, &submitInfos, self.inFlightFences[self.currentFrame]) }?;
		let presentInfo = vk::PresentInfoKHR::default()
			.wait_semaphores(&renderFinishedSemaphores)
			.swapchains(&swapchains)
			.image_indices(&imageIndices);
		let _ = unsafe { self.swapchainDevice.queue_present(self.presentQueue, &presentInfo) }?;
		self.currentFrame = (self.currentFrame + 1) % Self::MAX_FRAMES_IN_FLIGHT;
		Ok(())
	}
	pub fn new(dimensions: (u32, u32), eventLoop: &EventLoop<()>) -> Result<Self> {
		let (windows, windowID) = Self::createWindow(dimensions, "TEST", eventLoop)?;

		let entry = unsafe { ash::Entry::load() }?;
		let instance = Self::createInstance(&entry, eventLoop)?;
		let (debugInstance,  debugMessenger) = Self::setupDebugMessenger(&entry, &instance)?;

		let surfaceInstance = khr::surface::Instance::new(&entry, &instance);
		let surface = Self::createSurface(&entry, &instance, &windows[&windowID])?;
		let physicalDevice = Self::pickPhysicalDevice(&instance, &surfaceInstance, surface)?;
		let (logicalDevice, graphicsQueue, presentQueue) = Self::createLogicalDevice(&instance, &surfaceInstance, surface, physicalDevice)?;

		let (swapchainInstance, swapchainDevice, swapchainFormat, swapchainExtent, swapchain, swapchainImages) = Self::createSwapchain(&entry, &instance, &windows[&windowID], &surfaceInstance, surface, physicalDevice, &logicalDevice)?;
		let swapchainImageViews = Self::createSwapchainImageViews(&logicalDevice, swapchainFormat, &swapchainImages)?;

		let compiler = shaderc::Compiler::new().unwrap();
		let options = shaderc::CompileOptions::new().unwrap();
		let vertexShaderString = std::fs::read_to_string("assets/shaders/vertexshader.glsl")?;
		let vertexArtifact = compiler.compile_into_spirv(&vertexShaderString, shaderc::ShaderKind::Vertex, "vertexshader.glsl", "main", Some(&options))?;
		std::fs::write("assets/shaders/vertexshader.spirv", vertexArtifact.as_binary_u8())?;
		let fragmentShaderString = std::fs::read_to_string("assets/shaders/fragmentshader.glsl")?;
		let fragmentArtifact = compiler.compile_into_spirv(&fragmentShaderString, shaderc::ShaderKind::Fragment, "fragmentshader.glsl", "main", Some(&options))?;
		std::fs::write("assets/shaders/fragmentshader.spirv", fragmentArtifact.as_binary_u8())?;
		// let mut vertexShaderBinary = std::fs::File::open("assets/shaders/vertexshader.spirv")?;
		// let vertexShader = ash::util::read_spv(&mut vertexShaderBinary)?;
		// let mut fragmentShaderBinary = std::fs::File::open("assets/shaders/fragmentshader.spirv")?;
		// let fragmentShader = ash::util::read_spv(&mut fragmentShaderBinary)?;

		let renderPass = Self::createRenderpass(&logicalDevice, swapchainFormat)?;
		let (pipelineLayout, graphicsPipeline) = Self::createGraphicsPipeline(vertexArtifact.as_binary(), fragmentArtifact.as_binary(), &logicalDevice, renderPass)?;
		let swapchainFrameBuffers = Self::createFrameBuffers(&logicalDevice, renderPass, swapchainExtent, &swapchainImageViews)?;
	
		let commandPool = Self::createCommandPool(&instance, &logicalDevice, &surfaceInstance, surface, physicalDevice)?;
		let commandBuffers = Self::createCommandBuffers(&logicalDevice, commandPool)?;
		let (imageAvailableSemaphores, renderFinishedSemaphores, inFlightFences) = Self::createSyncObjects(&logicalDevice)?;
		Ok(Self {
			entry,
			instance,
			physicalDevice,
			logicalDevice,
			graphicsQueue,
			presentQueue,
			swapchainFormat,
			swapchainInstance,
			swapchainDevice,
			swapchainExtent,
			swapchain,
			swapchainImages,
			swapchainImageViews,
			swapchainFrameBuffers,
			recreateSwapchain: false,
			pipelineLayout,
			renderPass,
			graphicsPipeline,
			commandPool,
			commandBuffers,
			imageAvailableSemaphores,
			renderFinishedSemaphores,
			inFlightFences,
			currentFrame: 0,
			surfaceInstance,
			surface,
			debugInstance,
			debugMessenger,
			windows,
		})
	}
}

impl Drop for Application {
	fn drop(&mut self) {
		unsafe {
			self.logicalDevice.destroy_pipeline_layout(self.pipelineLayout, None);
			for framebuffer in &self.swapchainFrameBuffers {
				self.logicalDevice.destroy_framebuffer(*framebuffer, None);
			}
			self.logicalDevice.destroy_render_pass(self.renderPass, None);
			self.logicalDevice.destroy_pipeline(self.graphicsPipeline, None);
			self.logicalDevice.destroy_command_pool(self.commandPool, None);
			for semaphore in &self.imageAvailableSemaphores {
				self.logicalDevice.destroy_semaphore(*semaphore, None);
			}
			for semaphore in &self.renderFinishedSemaphores {
				self.logicalDevice.destroy_semaphore(*semaphore, None);
			}
			for fence in &self.inFlightFences {
				self.logicalDevice.destroy_fence(*fence, None);
			}
			for imageView in &self.swapchainImageViews {
				self.logicalDevice.destroy_image_view(*imageView, None);
			}
			self.logicalDevice.destroy_device(None);
			if Self::VALIDATION { self.debugInstance.destroy_debug_utils_messenger(self.debugMessenger, None); }
			self.instance.destroy_instance(None);
		}
	}
}

impl ApplicationHandler for Application {
	fn new_events(&mut self, eventLoop: &ActiveEventLoop, cause: winit::event::StartCause) {
		let _ = eventLoop;
		let _ = cause;
	}
	fn exiting(&mut self, eventLoop: &ActiveEventLoop) {
		let _ = eventLoop;
	}
	fn suspended(&mut self, eventLoop: &ActiveEventLoop) {
		let _ = eventLoop;
	}
	fn user_event(&mut self, eventLoop: &ActiveEventLoop, _event: ()) {
		let _ = eventLoop;
	}
	fn device_event(&mut self, eventLoop: &ActiveEventLoop, device_id: winit::event::DeviceId, event: winit::event::DeviceEvent) {
		let _ = eventLoop;
		let _ = device_id;
		let _ = event;
	}
	fn about_to_wait(&mut self, eventLoop: &ActiveEventLoop) {
		let _ = eventLoop;
	}
	fn memory_warning(&mut self, eventLoop: &ActiveEventLoop) {
		let _ = eventLoop;
	}
	fn resumed(&mut self, eventLoop: &ActiveEventLoop) {
		let _ = eventLoop;
	}
	fn window_event(&mut self, eventLoop: &ActiveEventLoop, window_id: WindowId, event: WindowEvent) {
		match event {
			WindowEvent::ActivationTokenDone { serial: _, token: _ } => {},
			WindowEvent::AxisMotion { device_id: _, axis: _, value: _ } => {},
			WindowEvent::CloseRequested => {
				unsafe {
					self.logicalDevice.device_wait_idle().unwrap();
					self.swapchainDevice.destroy_swapchain(self.swapchain, None);
					self.surfaceInstance.destroy_surface(self.surface, None);
				}
				self.windows.remove(&window_id);
				eventLoop.exit();
			},
			WindowEvent::CursorEntered { device_id: _ } => {},
			WindowEvent::CursorLeft { device_id: _ } => {},
			WindowEvent::CursorMoved { device_id: _, position: _ } => {},
			WindowEvent::Destroyed => {},
			WindowEvent::DoubleTapGesture { device_id: _ } => {},
			WindowEvent::DroppedFile(_path) => {},
			WindowEvent::Focused(_isFocused) => {},
			WindowEvent::HoveredFile(_path) => {},
			WindowEvent::HoveredFileCancelled => {},
			WindowEvent::Ime(_ime) => {},
			WindowEvent::KeyboardInput { device_id: _, event: _, is_synthetic: _ } => {},
			WindowEvent::ModifiersChanged(_modifiers) => {},
			WindowEvent::MouseInput { device_id: _, state: _, button: _ } => {},
			WindowEvent::MouseWheel { device_id: _, delta: _, phase: _ } => {},
			WindowEvent::Moved(_position) => {},
			WindowEvent::Occluded(_isOccluded) => {},
			WindowEvent::PanGesture { device_id: _, delta: _, phase: _ } => {},
			WindowEvent::PinchGesture { device_id: _, delta: _, phase: _ } => {},
			WindowEvent::RedrawRequested => self.draw().unwrap(),
			WindowEvent::Resized(_size) => {
				// self.recreateSwapchain = true;
			},
			WindowEvent::RotationGesture { device_id: _, delta: _, phase: _ } => {},
			WindowEvent::ScaleFactorChanged { scale_factor: _, inner_size_writer: _ } => {},
			WindowEvent::ThemeChanged(_theme) => {},
			WindowEvent::Touch(_touch) => {},
			WindowEvent::TouchpadPressure { device_id: _, pressure: _, stage: _ } => {},
		}
	}
}

pub fn test() -> Result<()> {
	let eventLoop = EventLoop::new()?;
	let mut app = Application::new((800, 800), &eventLoop)?;
	Ok(eventLoop.run_app(&mut app)?)
}

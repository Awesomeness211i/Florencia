use super::Result;
use ash::{
	self, khr, vk::{self, Handle}
};
use raw_window_handle::{HasDisplayHandle, HasWindowHandle};
use winit::{
	application::ApplicationHandler,
	event::WindowEvent,
	event_loop::{ ActiveEventLoop, EventLoop },
	window::{ Window, WindowAttributes, WindowId },
	dpi,
};

struct Application {
	entry: ash::Entry,
	instance: ash::Instance,
	physicalDevice: vk::PhysicalDevice,
	logicalDevice: ash::Device,
	queue: vk::Queue,
	swapchainFormat: vk::Format,
	swapchainDevice: khr::swapchain::Device,
	swapchain: vk::SwapchainKHR,
	swapchainImages: Vec<vk::Image>,
	swapchainImageViews: Vec<vk::ImageView>,
	recreateSwapchain: bool,
	pipelineLayout: vk::PipelineLayout,
	graphicsPipeline: vk::Pipeline,
	commandPool: vk::CommandPool,
	commandBuffer: vk::CommandBuffer,
	imageAvailableSemaphore: vk::Semaphore,
	renderFinishedSemaphore: vk::Semaphore,
	inFlightFence: vk::Fence,

	width: u32,
	height: u32,

	surfaceInstance: khr::surface::Instance,
	surface: vk::SurfaceKHR,

	window: Option<Window>,
}

impl Application {
	pub fn new(eventLoop: &EventLoop<()>) -> Result<Self> {
		let entry = unsafe { ash::Entry::load() }?;
		let instance = {
			let appName = c"App Name";
			let engineName = c"Engine Name";
			let applicationInfo = vk::ApplicationInfo::default()
				.application_name(appName)
				.application_version(0)
				.engine_name(engineName)
				.engine_version(0)
				.api_version(vk::API_VERSION_1_3);
			let requiredExtensions = ash_window::enumerate_required_extensions(eventLoop.display_handle()?.into())?;
			let instanceCreateInfo = vk::InstanceCreateInfo::default()
				.application_info(&applicationInfo)
				.enabled_extension_names(requiredExtensions);
			unsafe { entry.create_instance(&instanceCreateInfo, None) }?
		};

		let physicalDevice = unsafe { instance.enumerate_physical_devices() }?[0];

		// let queuefamilyproperties = unsafe { instance.get_physical_device_queue_family_properties(physicalDevice) };

		let logicalDevice = {
			let deviceQueuePriorities = [
				0.0,
			];
			let deviceQueueCreateInfos = [
				vk::DeviceQueueCreateInfo::default()
					.queue_family_index(0)
					.queue_priorities(&deviceQueuePriorities),
			];
			let deviceExtensionNames = [
				khr::swapchain::NAME.as_ptr(),
			];
			let mut dynamicRenderingFeatures = vk::PhysicalDeviceDynamicRenderingFeatures::default()
				.dynamic_rendering(true);
			let mut physicalDeviceSynchronization2Features = vk::PhysicalDeviceSynchronization2Features::default()
				.synchronization2(true);
			let mut physicalDeviceFeatures2 = vk::PhysicalDeviceFeatures2::default()
				.push_next(&mut physicalDeviceSynchronization2Features);
			let deviceCreateInfo = vk::DeviceCreateInfo::default()
				.queue_create_infos(&deviceQueueCreateInfos)
				.enabled_extension_names(&deviceExtensionNames)
				.push_next(&mut dynamicRenderingFeatures)
				.push_next(&mut physicalDeviceFeatures2);
			unsafe { instance.create_device(physicalDevice, &deviceCreateInfo, None) }?
		};

		let queue = unsafe { logicalDevice.get_device_queue(0, 0) };

		let swapchainFormat = vk::Format::B8G8R8A8_UNORM;
		// let swapchainInstance = khr::swapchain::Instance::new(&entry, &instance);
		let swapchain = vk::SwapchainKHR::null();
		let swapchainDevice = khr::swapchain::Device::new(&instance, &logicalDevice);
		let swapchainImages = Vec::new();
		let swapchainImageViews = Vec::new();

		// TODO: use std::path::Path::new("").exists() and std::fs::read_to_string() to check if I have already compiled the files
		// then use the already compiled ones if they exist
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
		// let vertexShader = match std::fs::File::open("assets/shaders/vertexshader.spirv") {

		let vertexShaderModule = {
			let shaderModuleCreateInfo = vk::ShaderModuleCreateInfo::default()
				.code(vertexArtifact.as_binary());
			unsafe { logicalDevice.create_shader_module(&shaderModuleCreateInfo, None) }?
		};
		let fragmentShaderModule = {
			let shaderModuleCreateInfo = vk::ShaderModuleCreateInfo::default()
				.code(fragmentArtifact.as_binary());
			unsafe { logicalDevice.create_shader_module(&shaderModuleCreateInfo, None) }?
		};

		let vertexShaderStageCreateInfo = vk::PipelineShaderStageCreateInfo::default()
			.stage(vk::ShaderStageFlags::VERTEX)
			.module(vertexShaderModule)
			.name(c"main");
		let fragmentShaderStageCreateInfo = vk::PipelineShaderStageCreateInfo::default()
			.stage(vk::ShaderStageFlags::FRAGMENT)
			.module(fragmentShaderModule)
			.name(c"main");

		let shaderStages = [
			vertexShaderStageCreateInfo,
			fragmentShaderStageCreateInfo,
		];

		let pipelineLayout = {
			let pipelineLayoutCreateInfo = vk::PipelineLayoutCreateInfo::default();
			unsafe { logicalDevice.create_pipeline_layout(&pipelineLayoutCreateInfo, None) }?
		};

		let width = 800;
		let height = 800;

		let graphicsPipeline = {
			let dynamicStateCreateInfo = vk::PipelineDynamicStateCreateInfo::default();
			let vertexInputStateCreateInfo = vk::PipelineVertexInputStateCreateInfo::default();
			let inputAssemblyStateCreateInfo = vk::PipelineInputAssemblyStateCreateInfo::default()
				.topology(vk::PrimitiveTopology::TRIANGLE_LIST);
			let viewport = vk::Viewport::default()
				.width(width as f32)
				.height(height as f32);
			let viewports = [
				viewport,
			];
			let extent = vk::Extent2D::default()
				.width(width)
				.height(height);
			let scissor = vk::Rect2D::default()
				.extent(extent);
			let scissors = [
				scissor,
			];
			let viewportStateCreateInfo = vk::PipelineViewportStateCreateInfo::default()
				.viewports(&viewports)
				.scissors(&scissors);
			let rasterizationStateCreateInfo = vk::PipelineRasterizationStateCreateInfo::default()
				.polygon_mode(vk::PolygonMode::FILL)
				.front_face(vk::FrontFace::COUNTER_CLOCKWISE)
				.cull_mode(vk::CullModeFlags::BACK)
				.line_width(1.0);
			let multisampleStateCreateInfo = vk::PipelineMultisampleStateCreateInfo::default()
				.rasterization_samples(vk::SampleCountFlags::TYPE_1);
			let attachment = vk::PipelineColorBlendAttachmentState::default()
				.color_write_mask(vk::ColorComponentFlags::RGBA);
			let attachments = [
				attachment,
			];
			let colorBlendStateCreateInfo = vk::PipelineColorBlendStateCreateInfo::default()
				.attachments(&attachments);
			let colorFormats = [
				swapchainFormat,
			];
			let mut renderingCreateInfo = vk::PipelineRenderingCreateInfo::default()
				.color_attachment_formats(&colorFormats);
			let graphicsPipelineCreateInfo = vk::GraphicsPipelineCreateInfo::default()
				.layout(pipelineLayout)
				.stages(&shaderStages)
				.dynamic_state(&dynamicStateCreateInfo)
				.vertex_input_state(&vertexInputStateCreateInfo)
				.input_assembly_state(&inputAssemblyStateCreateInfo)
				.viewport_state(&viewportStateCreateInfo)
				.rasterization_state(&rasterizationStateCreateInfo)
				.multisample_state(&multisampleStateCreateInfo)
				.color_blend_state(&colorBlendStateCreateInfo)
				.render_pass(vk::RenderPass::null())
				.push_next(&mut renderingCreateInfo);
			let graphicsPipelineCreateInfos = [
				graphicsPipelineCreateInfo,
			];
			unsafe { logicalDevice.create_graphics_pipelines(vk::PipelineCache::null(), &graphicsPipelineCreateInfos, None) }.unwrap()[0]
		};

		unsafe {
			logicalDevice.destroy_shader_module(vertexShaderModule, None);
			logicalDevice.destroy_shader_module(fragmentShaderModule, None);
		}

		let commandPool = {
			let commandPoolCreateInfo = vk::CommandPoolCreateInfo::default()
				.queue_family_index(0);
			unsafe { logicalDevice.create_command_pool(&commandPoolCreateInfo, None) }?
		};
		let commandBuffer = {
			let commandBufferAllocateInfo = vk::CommandBufferAllocateInfo::default()
				.level(vk::CommandBufferLevel::PRIMARY)
				.command_pool(commandPool)
				.command_buffer_count(1);
			unsafe { logicalDevice.allocate_command_buffers(&commandBufferAllocateInfo) }?[0]
		};

		let imageAvailableSemaphore = {
			let semaphoreCreateInfo = vk::SemaphoreCreateInfo::default();
			unsafe { logicalDevice.create_semaphore(&semaphoreCreateInfo, None) }?
		};
		let renderFinishedSemaphore = {
			let semaphoreCreateInfo = vk::SemaphoreCreateInfo::default();
			unsafe { logicalDevice.create_semaphore(&semaphoreCreateInfo, None) }?
		};
		let inFlightFence = {
			let fenceCreateInfo = vk::FenceCreateInfo::default();
			unsafe { logicalDevice.create_fence(&fenceCreateInfo, None) }?
		};

		// let window = WindowBuilder::new()
		// 	.with_title("TEST")
		// 	.with_inner_size(winit::dpi::LogicalSize::new(800, 800))
		// 	.with_visible(true)
		// 	.with_resizable(true)
		// 	.with_window_icon(None)
		// 	.build(&eventLoop)?;

		let surfaceInstance = khr::surface::Instance::new(&entry, &instance);
		// let window = eventLoop.create_window(window_attributes)?;
		// let surface = unsafe {
		// 	ash_window::create_surface(&entry, &instance, eventLoop.raw_display_handle()?, window.raw_window_handle()?, None)
		// }?;
		Ok(Self {
			entry,
			instance,
			physicalDevice,
			logicalDevice,
			queue,
			swapchainFormat,
			swapchainDevice,
			swapchain,
			swapchainImages,
			swapchainImageViews,
			recreateSwapchain: true,
			pipelineLayout,
			graphicsPipeline,
			commandPool,
			commandBuffer,
			imageAvailableSemaphore,
			renderFinishedSemaphore,
			inFlightFence,

			width,
			height,

			surfaceInstance,
			surface: vk::SurfaceKHR::null(),

			window: None,
		})
	}
}

impl Drop for Application {
	fn drop(&mut self) {
		unsafe {
			self.logicalDevice.destroy_pipeline_layout(self.pipelineLayout, None);
			self.logicalDevice.destroy_pipeline(self.graphicsPipeline, None);
			self.logicalDevice.destroy_command_pool(self.commandPool, None);
			self.logicalDevice.destroy_semaphore(self.imageAvailableSemaphore, None);
			self.logicalDevice.destroy_semaphore(self.renderFinishedSemaphore, None);
			self.logicalDevice.destroy_fence(self.inFlightFence, None);
			for imageView in &self.swapchainImageViews {
				self.logicalDevice.destroy_image_view(*imageView, None);
			}
			for image in &self.swapchainImages {
				self.logicalDevice.destroy_image(*image, None);
			}
			self.swapchainDevice.destroy_swapchain(self.swapchain, None);
			self.logicalDevice.destroy_device(None);
			self.surfaceInstance.destroy_surface(self.surface, None);
			self.instance.destroy_instance(None);
		}
	}
}

impl ApplicationHandler for Application {
	fn resumed(&mut self, event_loop: &ActiveEventLoop) {
		let windowAttributes = WindowAttributes::default()
			.with_title("TEST")
			.with_inner_size(dpi::LogicalSize::new(self.width, self.height))
			.with_visible(true)
			.with_resizable(true)
			.with_window_icon(None);
		self.window = Some(event_loop.create_window(windowAttributes).unwrap());
	}
	fn window_event(&mut self, event_loop: &ActiveEventLoop, window_id: WindowId, event: WindowEvent) {
		// Event::MainEventsCleared => { window.request_redraw() },
		match event {
			WindowEvent::ActivationTokenDone { serial, token } => {},
			WindowEvent::AxisMotion { device_id, axis, value } => {},
			WindowEvent::CloseRequested => {
				if window_id == self.window.as_ref().unwrap().id() { self.window.take(); }
			},
			WindowEvent::CursorEntered { device_id } => {},
			WindowEvent::CursorLeft { device_id } => {},
			WindowEvent::CursorMoved { device_id, position } => {},
			WindowEvent::Destroyed => {},
			WindowEvent::DoubleTapGesture { device_id } => {},
			WindowEvent::DroppedFile(_path) => {},
			WindowEvent::Focused(_isFocused) => {},
			WindowEvent::HoveredFile(_) => {},
			WindowEvent::HoveredFileCancelled => {},
			WindowEvent::Ime(_) => {},
			WindowEvent::KeyboardInput { device_id, event, is_synthetic } => {},
			WindowEvent::ModifiersChanged(_) => {},
			WindowEvent::MouseInput { device_id, state, button } => {},
			WindowEvent::MouseWheel { device_id, delta, phase } => {},
			WindowEvent::Moved(_) => {},
			WindowEvent::Occluded(_isOccluded) => {},
			WindowEvent::PanGesture { device_id, delta, phase } => {},
			WindowEvent::PinchGesture { device_id, delta, phase } => {},
			WindowEvent::RedrawRequested => {
				if self.recreateSwapchain {
					self.surface = if self.surface.is_null() {
						unsafe {
							ash_window::create_surface(&self.entry, &self.instance, self.window.as_ref().unwrap().display_handle().unwrap().into(), self.window.as_ref().unwrap().window_handle().unwrap().into(), None)
						}
					} else {
						unsafe {
							self.surfaceInstance.destroy_surface(self.surface, None);
							ash_window::create_surface(&self.entry, &self.instance, self.window.as_ref().unwrap().display_handle().unwrap().into(), self.window.as_ref().unwrap().window_handle().unwrap().into(), None)
						}
					}.unwrap();
					self.swapchain = {
						let queueFamilyIndices = [
							0,
						];
						let surfaceCapabilities = unsafe { self.surfaceInstance.get_physical_device_surface_capabilities(self.physicalDevice, self.surface) }.unwrap();
						// let surfaceFormats = unsafe { self.surfaceInstance.get_physical_device_surface_formats(physicalDevice, surface) }.unwrap();
						let extent = vk::Extent2D::default()
							.width(self.width)
							.height(self.height);
						let swapchainCreateInfo = vk::SwapchainCreateInfoKHR::default()
							.surface(self.surface)
							.clipped(true)
							.composite_alpha(vk::CompositeAlphaFlagsKHR::OPAQUE)
							.image_array_layers(1)
							.image_color_space(vk::ColorSpaceKHR::SRGB_NONLINEAR)
							.image_format(self.swapchainFormat)
							.image_sharing_mode(vk::SharingMode::EXCLUSIVE)
							.min_image_count(surfaceCapabilities.min_image_count + 1)
							.pre_transform(surfaceCapabilities.current_transform)
							.image_extent(extent)
							.image_usage(vk::ImageUsageFlags::COLOR_ATTACHMENT)
							.present_mode(vk::PresentModeKHR::FIFO)
							.queue_family_indices(&queueFamilyIndices);

						unsafe { self.swapchainDevice.create_swapchain(&swapchainCreateInfo, None) }.unwrap()
					};

					self.swapchainImages = unsafe { self.swapchainDevice.get_swapchain_images(self.swapchain) }.unwrap();

					self.swapchainImageViews.clear();
					self.swapchainImages.iter().copied().map(|image| {
						let imageSubresourceRange = vk::ImageSubresourceRange::default()
							.aspect_mask(vk::ImageAspectFlags::COLOR)
							.level_count(1)
							.layer_count(1);
						let imageViewCreateInfo = vk::ImageViewCreateInfo::default()
							.image(image)
							.format(self.swapchainFormat)
							.view_type(vk::ImageViewType::TYPE_2D)
							.subresource_range(imageSubresourceRange);
						unsafe { self.logicalDevice.create_image_view(&imageViewCreateInfo, None) }.unwrap()
					}).for_each(|imageView| { self.swapchainImageViews.push(imageView); });
				}

				let (imageIndex, _isSuboptimal) = unsafe {
					let aquireNextImageInfo = vk::AcquireNextImageInfoKHR::default()
						.swapchain(self.swapchain)
						.timeout(u64::MAX)
						.semaphore(self.imageAvailableSemaphore)
						.device_mask(1);
					self.swapchainDevice.acquire_next_image2(&aquireNextImageInfo)
				}.unwrap();

				let commandBufferBeginInfo = vk::CommandBufferBeginInfo::default();
				unsafe { self.logicalDevice.begin_command_buffer(self.commandBuffer, &commandBufferBeginInfo) }.unwrap();
				let subresourceRangeTop = vk::ImageSubresourceRange::default()
					.layer_count(1)
					.level_count(1)
					.aspect_mask(vk::ImageAspectFlags::COLOR);
				let imageMemoryBarrierTop = vk::ImageMemoryBarrier2::default()
					.image(self.swapchainImages[imageIndex as usize])
					.old_layout(vk::ImageLayout::UNDEFINED)
					.new_layout(vk::ImageLayout::ATTACHMENT_OPTIMAL)
					.src_access_mask(vk::AccessFlags2::COLOR_ATTACHMENT_WRITE)
					.subresource_range(subresourceRangeTop)
					.src_stage_mask(vk::PipelineStageFlags2::COLOR_ATTACHMENT_OUTPUT)
					.dst_stage_mask(vk::PipelineStageFlags2::BOTTOM_OF_PIPE);
				let imageMemoryBarriersTop = [
					imageMemoryBarrierTop,
				];
				let dependencyInfoTop = vk::DependencyInfo::default()
					.image_memory_barriers(&imageMemoryBarriersTop);
				unsafe { self.logicalDevice.cmd_pipeline_barrier2(self.commandBuffer, &dependencyInfoTop) };
				let extent = vk::Extent2D::default()
					.width(self.width)
					.height(self.height);
				let renderArea = vk::Rect2D::default()
					.extent(extent);
				let renderingAttachmentInfo = vk::RenderingAttachmentInfo::default()
					.image_view(self.swapchainImageViews[imageIndex as usize])
					.load_op(vk::AttachmentLoadOp::CLEAR)
					.store_op(vk::AttachmentStoreOp::STORE)
					.clear_value(vk::ClearValue::default())
					.image_layout(vk::ImageLayout::COLOR_ATTACHMENT_OPTIMAL);
				let renderingAttachmentInfos = [
					renderingAttachmentInfo,
				];
				let renderingInfo = vk::RenderingInfo::default()
					.render_area(renderArea)
					.layer_count(1)
					.color_attachments(&renderingAttachmentInfos);
				unsafe { self.logicalDevice.cmd_begin_rendering(self.commandBuffer, &renderingInfo) };

				unsafe { self.logicalDevice.cmd_bind_pipeline(self.commandBuffer, vk::PipelineBindPoint::GRAPHICS, self.graphicsPipeline) };
				unsafe { self.logicalDevice.cmd_draw(self.commandBuffer, 3, 1, 0, 0) };

				unsafe { self.logicalDevice.cmd_end_rendering(self.commandBuffer) };
				let subresourceRangeBottom = vk::ImageSubresourceRange::default()
					.layer_count(1)
					.level_count(1)
					.aspect_mask(vk::ImageAspectFlags::COLOR);
				let imageMemoryBarrierBottom = vk::ImageMemoryBarrier2::default()
					.image(self.swapchainImages[imageIndex as usize])
					.old_layout(vk::ImageLayout::ATTACHMENT_OPTIMAL)
					.new_layout(vk::ImageLayout::PRESENT_SRC_KHR)
					.src_access_mask(vk::AccessFlags2::COLOR_ATTACHMENT_WRITE)
					.subresource_range(subresourceRangeBottom)
					.src_stage_mask(vk::PipelineStageFlags2::COLOR_ATTACHMENT_OUTPUT)
					.dst_stage_mask(vk::PipelineStageFlags2::BOTTOM_OF_PIPE);
				let imageMemoryBarriersBottom = [
					imageMemoryBarrierBottom,
				];
				let dependencyInfoBottom = vk::DependencyInfo::default()
					.image_memory_barriers(&imageMemoryBarriersBottom);
				unsafe { self.logicalDevice.cmd_pipeline_barrier2(self.commandBuffer, &dependencyInfoBottom) };
				unsafe { self.logicalDevice.end_command_buffer(self.commandBuffer) }.unwrap();

				let commandBufferSubmitInfo = vk::CommandBufferSubmitInfo::default()
					.command_buffer(self.commandBuffer);
				let commandBufferSubmitInfos = [
					commandBufferSubmitInfo,
				];
				let waitSemaphoreInfo = vk::SemaphoreSubmitInfo::default()
					.semaphore(self.imageAvailableSemaphore)
					.stage_mask(vk::PipelineStageFlags2::COLOR_ATTACHMENT_OUTPUT);
				let waitSemaphoreInfos = [
					waitSemaphoreInfo,
				];
				let signalSemaphoreInfo = vk::SemaphoreSubmitInfo::default()
					.semaphore(self.renderFinishedSemaphore)
					.stage_mask(vk::PipelineStageFlags2::TRANSFER);
				let signalSemaphoreInfos = [
					signalSemaphoreInfo,
				];
				let submitInfo = vk::SubmitInfo2::default()
					.command_buffer_infos(&commandBufferSubmitInfos)
					.wait_semaphore_infos(&waitSemaphoreInfos)
					.signal_semaphore_infos(&signalSemaphoreInfos);
				let submitInfos = [
					submitInfo,
				];
				if unsafe { self.logicalDevice.queue_submit2(self.queue, &submitInfos, self.inFlightFence) }.is_ok() {
					self.recreateSwapchain = false;
				}

				let imageIndices = [
					imageIndex,
				];
				let renderFinishedSemaphores = [
					self.renderFinishedSemaphore,
				];
				let swapchains = [
					self.swapchain,
				];
				let presentInfo = vk::PresentInfoKHR::default()
					.swapchains(&swapchains)
					.image_indices(&imageIndices)
					.wait_semaphores(&renderFinishedSemaphores);
				let _isSuboptimalPost = unsafe { self.swapchainDevice.queue_present(self.queue, &presentInfo) }.unwrap();
				unsafe {
					let inFlightFences = [
						self.inFlightFence,
					];
					self.logicalDevice.wait_for_fences(&inFlightFences, false, u64::MAX).unwrap();
					self.logicalDevice.reset_fences(&inFlightFences).unwrap();
					self.logicalDevice.reset_command_pool(self.commandPool, vk::CommandPoolResetFlags::empty()).unwrap();
				}
			},
			WindowEvent::Resized(size) => {
				// self.width = size.width;
				// self.height = size.height;
				// self.recreateSwapchain = true;
			},
			WindowEvent::RotationGesture { device_id, delta, phase } => {},
			WindowEvent::ScaleFactorChanged { scale_factor, inner_size_writer } => {},
			WindowEvent::ThemeChanged(_) => {},
			WindowEvent::Touch(_) => {},
			WindowEvent::TouchpadPressure { device_id, pressure, stage } => {},
		}
	}
}

pub fn test2() -> Result<()> {
	Ok(())
}

pub fn test() -> Result<()> {
	let eventLoop = EventLoop::new()?;
	let mut app = Application::new(&eventLoop)?;
	eventLoop.run_app(&mut app)?;
	Ok(())
}

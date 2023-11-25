use ash::{
	self,
	vk,
	extensions::{
		khr,
	},
};
use winit::{
	event_loop::EventLoop,
	window::{
		WindowBuilder,
	},
	event::{WindowEvent, Event},
};
use raw_window_handle::{HasRawDisplayHandle, HasRawWindowHandle};

use super::Result;

pub fn test() -> Result<()> {
	let swapchainFormat = vk::Format::B8G8R8A8_UNORM;
	let eventLoop = EventLoop::new();
	let window = WindowBuilder::new()
		.with_title("TEST")
		// .with_inner_size(winit::dpi::LogicalSize::new(1920, 1080))
		.with_visible(true)
		.with_resizable(true)
		.build(&eventLoop)?;

	let entry = unsafe { ash::Entry::load() }?;
	let instance = {
		let appName = std::ffi::CString::new("App Name")?;
		let engineName = std::ffi::CString::new("Engine Name")?;
		let applicationInfo = vk::ApplicationInfo::builder()
			.application_name(&appName)
			.application_version(0)
			.engine_name(&engineName)
			.engine_version(0)
			.api_version(vk::API_VERSION_1_3);
		let requiredExtensions = ash_window::enumerate_required_extensions(window.raw_display_handle())?;
		let instanceCreateInfo = vk::InstanceCreateInfo::builder()
			.application_info(&applicationInfo)
			.enabled_extension_names(requiredExtensions);
		unsafe { entry.create_instance(&instanceCreateInfo, None) }?
	};

	let surfaceExtension = khr::Surface::new(&entry, &instance);

	let surface = unsafe {
		ash_window::create_surface(&entry, &instance, window.raw_display_handle(), window.raw_window_handle(), None)
	}?;

	let physicalDevice = unsafe { instance.enumerate_physical_devices() }?[0];

	let device = {
		let deviceQueuePriorities = [
			0.0,
		];
		let deviceQueueCreateInfos = [
			vk::DeviceQueueCreateInfo::builder()
				.queue_family_index(0)
				.queue_priorities(&deviceQueuePriorities)
				.build(),
		];
		let deviceExtensionNames = [
			khr::Swapchain::name().as_ptr(),
		];
		let mut dynamicRenderingFeatures = vk::PhysicalDeviceDynamicRenderingFeatures::builder()
			.dynamic_rendering(true);
		let mut physicalDeviceSynchronization2Features = vk::PhysicalDeviceSynchronization2Features::builder()
			.synchronization2(true);
		let mut physicalDeviceFeatures2 = vk::PhysicalDeviceFeatures2::builder()
			.push_next(&mut physicalDeviceSynchronization2Features);
		let deviceCreateInfo = vk::DeviceCreateInfo::builder()
			.queue_create_infos(&deviceQueueCreateInfos)
			.enabled_extension_names(&deviceExtensionNames)
			.push_next(&mut dynamicRenderingFeatures)
			.push_next(&mut physicalDeviceFeatures2);
		unsafe { instance.create_device(physicalDevice, &deviceCreateInfo, None) }?
	};

	let queue = unsafe { device.get_device_queue(0, 0) };

	let swapchainExtension = khr::Swapchain::new(&instance, &device);

	let mut swapchain = vk::SwapchainKHR::null();

	let mut swapchainImages = Vec::new();

	let mut swapchainImageViews = Vec::new();

	// TODO: use std::path::Path::new("").exists() and std::fs::read_to_string() to check if I have already compiled the files
	// then use the already compiled ones if they exist
	let compiler = shaderc::Compiler::new().unwrap();
	let options = shaderc::CompileOptions::new().unwrap();
	let vertexShader = std::fs::read_to_string("assets/shaders/vertexshader.glsl")?;
	let vertexArtifact = compiler.compile_into_spirv(&vertexShader, shaderc::ShaderKind::Vertex, "vertexshader.glsl", "main", Some(&options))?;
	std::fs::write("assets/shaders/vertexshader.spirv", vertexArtifact.as_binary_u8())?;
	let fragmentShader = std::fs::read_to_string("assets/shaders/fragmentshader.glsl")?;
	let fragmentArtifact = compiler.compile_into_spirv(&fragmentShader, shaderc::ShaderKind::Fragment, "fragmentshader.glsl", "main", Some(&options))?;
	std::fs::write("assets/shaders/fragmentshader.spirv", fragmentArtifact.as_binary_u8())?;

	let vertexShaderModule = {
		let shaderModuleCreateInfo = vk::ShaderModuleCreateInfo::builder()
			.code(vertexArtifact.as_binary());
		unsafe { device.create_shader_module(&shaderModuleCreateInfo, None) }?
	};
	let fragmentShaderModule = {
		let shaderModuleCreateInfo = vk::ShaderModuleCreateInfo::builder()
			.code(fragmentArtifact.as_binary());
		unsafe { device.create_shader_module(&shaderModuleCreateInfo, None) }?
	};

	let vertexShaderStageCreateInfo = vk::PipelineShaderStageCreateInfo::builder()
		.stage(vk::ShaderStageFlags::VERTEX)
		.module(vertexShaderModule)
		.name(std::ffi::CStr::from_bytes_with_nul(b"main\0")?);
	let fragmentShaderStageCreateInfo = vk::PipelineShaderStageCreateInfo::builder()
		.stage(vk::ShaderStageFlags::FRAGMENT)
		.module(fragmentShaderModule)
		.name(std::ffi::CStr::from_bytes_with_nul(b"main\0")?);

	let shaderStages = [
		vertexShaderStageCreateInfo.build(),
		fragmentShaderStageCreateInfo.build(),
	];

	let pipelineLayout = {
		let pipelineLayoutCreateInfo = vk::PipelineLayoutCreateInfo::builder();
		unsafe { device.create_pipeline_layout(&pipelineLayoutCreateInfo, None) }?
	};

	let windowSize = window.inner_size();

	let grapicsPipeline = {
		let dynamicStateCreateInfo = vk::PipelineDynamicStateCreateInfo::builder();
		let vertexInputStateCreateInfo = vk::PipelineVertexInputStateCreateInfo::builder();
		let inputAssemblyStateCreateInfo = vk::PipelineInputAssemblyStateCreateInfo::builder()
			.topology(vk::PrimitiveTopology::TRIANGLE_LIST);
		let viewport = vk::Viewport::builder()
			.width(windowSize.width as f32)
			.height(windowSize.height as f32);
		let viewports = [
			viewport.build(),
		];
		let extent = vk::Extent2D::builder()
			.width(windowSize.width)
			.height(windowSize.height)
			.build();
		let scissor = vk::Rect2D::builder()
			.extent(extent);
		let scissors = [
			scissor.build(),
		];
		let viewportStateCreateInfo = vk::PipelineViewportStateCreateInfo::builder()
			.viewports(&viewports)
			.scissors(&scissors);
		let rasterizationStateCreateInfo = vk::PipelineRasterizationStateCreateInfo::builder()
			.polygon_mode(vk::PolygonMode::FILL)
			.front_face(vk::FrontFace::COUNTER_CLOCKWISE)
			.cull_mode(vk::CullModeFlags::BACK)
			.line_width(1.0);
		let multisampleStateCreateInfo = vk::PipelineMultisampleStateCreateInfo::builder()
			.rasterization_samples(vk::SampleCountFlags::TYPE_1);
		let attachment = vk::PipelineColorBlendAttachmentState::builder()
			.color_write_mask(vk::ColorComponentFlags::RGBA);
		let attachments = [
			attachment.build(),
		];
		let colorBlendStateCreateInfo = vk::PipelineColorBlendStateCreateInfo::builder()
			.attachments(&attachments);
		let colorFormats = [
			swapchainFormat,
		];
		let mut renderingCreateInfo = vk::PipelineRenderingCreateInfo::builder()
			.color_attachment_formats(&colorFormats);
		let graphicsPipelineCreateInfo = vk::GraphicsPipelineCreateInfo::builder()
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
			graphicsPipelineCreateInfo.build(),
		];
		unsafe { device.create_graphics_pipelines(vk::PipelineCache::null(), &graphicsPipelineCreateInfos, None) }.unwrap()[0]
	};

	unsafe {
		device.destroy_shader_module(vertexShaderModule, None);
		device.destroy_shader_module(fragmentShaderModule, None);
	}

	let commandPool = {
		let commandPoolCreateInfo = vk::CommandPoolCreateInfo::builder()
			.queue_family_index(0);
		unsafe { device.create_command_pool(&commandPoolCreateInfo, None) }?
	};
	let commandBuffer = {
		let commandBufferAllocateInfo = vk::CommandBufferAllocateInfo::builder()
			.level(vk::CommandBufferLevel::PRIMARY)
			.command_pool(commandPool)
			.command_buffer_count(1);
		unsafe { device.allocate_command_buffers(&commandBufferAllocateInfo) }?[0]
	};

	let imageAvailableSemaphore = {
		let semaphoreCreateInfo = vk::SemaphoreCreateInfo::builder();
		unsafe { device.create_semaphore(&semaphoreCreateInfo, None) }?
	};
	let renderFinishedSemaphore = {
		let semaphoreCreateInfo = vk::SemaphoreCreateInfo::builder();
		unsafe { device.create_semaphore(&semaphoreCreateInfo, None) }?
	};
	let inFlightFence = {
		let fenceCreateInfo = vk::FenceCreateInfo::builder();
		unsafe { device.create_fence(&fenceCreateInfo, None) }?
	};

	let mut shouldRecreateSwapchain = true;

	eventLoop.run(move |event, window_target, controlflow| {
		match event {
			Event::WindowEvent { event, window_id } => match event {
				WindowEvent::CloseRequested => { controlflow.set_exit() },
				_ => {},
			},
			Event::MainEventsCleared => window.request_redraw(),
			Event::RedrawRequested(id) => {
				if shouldRecreateSwapchain {
					swapchain = {
						let queueFamilyIndices = [
							0,
						];
						let surfaceCapabilities = unsafe { surfaceExtension.get_physical_device_surface_capabilities(physicalDevice, surface) }.unwrap();
						let surfaceFormats = unsafe { surfaceExtension.get_physical_device_surface_formats(physicalDevice, surface) }.unwrap();
						let extent = vk::Extent2D::builder()
							.width(windowSize.width)
							.height(windowSize.height)
							.build();
						let swapchainCreateInfo = vk::SwapchainCreateInfoKHR::builder()
							.surface(surface)
							.clipped(true)
							.composite_alpha(vk::CompositeAlphaFlagsKHR::OPAQUE)
							.image_array_layers(1)
							.image_color_space(vk::ColorSpaceKHR::SRGB_NONLINEAR)
							.image_format(swapchainFormat)
							.image_sharing_mode(vk::SharingMode::EXCLUSIVE)
							.min_image_count(surfaceCapabilities.min_image_count + 1)
							.pre_transform(surfaceCapabilities.current_transform)
							.image_extent(extent)
							.image_usage(vk::ImageUsageFlags::COLOR_ATTACHMENT)
							.present_mode(vk::PresentModeKHR::FIFO)
							.queue_family_indices(&queueFamilyIndices);

						unsafe { swapchainExtension.create_swapchain(&swapchainCreateInfo, None) }.unwrap()
					};

					swapchainImages = unsafe { swapchainExtension.get_swapchain_images(swapchain) }.unwrap();

					swapchainImageViews.clear();
					swapchainImages.iter().copied().map(|image| {
						let imageSubresourceRange = vk::ImageSubresourceRange::builder()
							.aspect_mask(vk::ImageAspectFlags::COLOR)
							.level_count(1)
							.layer_count(1)
							.build();
						let imageViewCreateInfo = vk::ImageViewCreateInfo::builder()
							.image(image)
							.format(vk::Format::B8G8R8A8_UNORM)
							.view_type(vk::ImageViewType::TYPE_2D)
							.subresource_range(imageSubresourceRange);
						unsafe { device.create_image_view(&imageViewCreateInfo, None) }.unwrap()
					}).for_each(|imageView| { swapchainImageViews.push(imageView); });
				}

				let (imageIndex, _isSuboptimal) = unsafe {
					let aquireNextImageInfo = vk::AcquireNextImageInfoKHR::builder()
						.swapchain(swapchain)
						.timeout(u64::MAX)
						.semaphore(imageAvailableSemaphore)
						.device_mask(1);
					swapchainExtension.acquire_next_image2(&aquireNextImageInfo)
				}.unwrap();

				unsafe {
					let commandBufferBeginInfo = vk::CommandBufferBeginInfo::builder();
					device.begin_command_buffer(commandBuffer, &commandBufferBeginInfo).unwrap();
					let subresourceRangeTop = vk::ImageSubresourceRange::builder()
						.layer_count(1)
						.level_count(1)
						.aspect_mask(vk::ImageAspectFlags::COLOR)
						.build();
					let imageMemoryBarrierTop = vk::ImageMemoryBarrier2::builder()
						.image(swapchainImages[imageIndex as usize])
						.old_layout(vk::ImageLayout::UNDEFINED)
						.new_layout(vk::ImageLayout::ATTACHMENT_OPTIMAL)
						.src_access_mask(vk::AccessFlags2::COLOR_ATTACHMENT_WRITE)
						.subresource_range(subresourceRangeTop)
						.src_stage_mask(vk::PipelineStageFlags2::COLOR_ATTACHMENT_OUTPUT)
						.dst_stage_mask(vk::PipelineStageFlags2::BOTTOM_OF_PIPE);
					let imageMemoryBarriersTop = [
						imageMemoryBarrierTop.build(),
					];
					let dependencyInfoTop = vk::DependencyInfo::builder()
						.image_memory_barriers(&imageMemoryBarriersTop);
					device.cmd_pipeline_barrier2(commandBuffer, &dependencyInfoTop);
					let extent = vk::Extent2D::builder()
						.width(windowSize.width)
						.height(windowSize.height)
						.build();
					let renderArea = vk::Rect2D::builder()
						.extent(extent)
						.build();
					let renderingAttachmentInfo = vk::RenderingAttachmentInfo::builder()
						.image_view(swapchainImageViews[imageIndex as usize])
						.load_op(vk::AttachmentLoadOp::CLEAR)
						.store_op(vk::AttachmentStoreOp::STORE)
						.clear_value(vk::ClearValue::default())
						.image_layout(vk::ImageLayout::COLOR_ATTACHMENT_OPTIMAL);
					let renderingAttachmentInfos = [
						renderingAttachmentInfo.build(),
					];
					let renderingInfo = vk::RenderingInfo::builder()
						.render_area(renderArea)
						.layer_count(1)
						.color_attachments(&renderingAttachmentInfos);
					device.cmd_begin_rendering(commandBuffer, &renderingInfo);

					device.cmd_bind_pipeline(commandBuffer, vk::PipelineBindPoint::GRAPHICS, grapicsPipeline);
					device.cmd_draw(commandBuffer, 3, 1, 0, 0);

					device.cmd_end_rendering(commandBuffer);
					let subresourceRangeBottom = vk::ImageSubresourceRange::builder()
						.layer_count(1)
						.level_count(1)
						.aspect_mask(vk::ImageAspectFlags::COLOR)
						.build();
					let imageMemoryBarrierBottom = vk::ImageMemoryBarrier2::builder()
						.image(swapchainImages[imageIndex as usize])
						.old_layout(vk::ImageLayout::ATTACHMENT_OPTIMAL)
						.new_layout(vk::ImageLayout::PRESENT_SRC_KHR)
						.src_access_mask(vk::AccessFlags2::COLOR_ATTACHMENT_WRITE)
						.subresource_range(subresourceRangeBottom)
						.src_stage_mask(vk::PipelineStageFlags2::COLOR_ATTACHMENT_OUTPUT)
						.dst_stage_mask(vk::PipelineStageFlags2::BOTTOM_OF_PIPE);
					let imageMemoryBarriersBottom = [
						imageMemoryBarrierBottom.build(),
					];
					let dependencyInfoBottom = vk::DependencyInfo::builder()
						.image_memory_barriers(&imageMemoryBarriersBottom);
					device.cmd_pipeline_barrier2(commandBuffer, &dependencyInfoBottom);
					device.end_command_buffer(commandBuffer).unwrap();

					let commandBufferSubmitInfo = vk::CommandBufferSubmitInfo::builder()
						.command_buffer(commandBuffer);
					let commandBufferSubmitInfos = [
						commandBufferSubmitInfo.build(),
					];
					let waitSemaphoreInfo = vk::SemaphoreSubmitInfo::builder()
						.semaphore(imageAvailableSemaphore)
						.stage_mask(vk::PipelineStageFlags2::COLOR_ATTACHMENT_OUTPUT);
					let waitSemaphoreInfos = [
						waitSemaphoreInfo.build(),
					];
					let signalSemaphoreInfo = vk::SemaphoreSubmitInfo::builder()
						.semaphore(renderFinishedSemaphore)
						.stage_mask(vk::PipelineStageFlags2::TRANSFER);
					let signalSemaphoreInfos = [
						signalSemaphoreInfo.build(),
					];
					let submitInfo = vk::SubmitInfo2::builder()
						.command_buffer_infos(&commandBufferSubmitInfos)
						.wait_semaphore_infos(&waitSemaphoreInfos)
						.signal_semaphore_infos(&signalSemaphoreInfos);
					let submitInfos = [
						submitInfo.build(),
					];
					match device.queue_submit2(queue, &submitInfos, inFlightFence) {
						Ok(_) => {
							shouldRecreateSwapchain = false;
						},
						Err(err) if err == vk::Result::SUBOPTIMAL_KHR => {
							shouldRecreateSwapchain = true;
						},
						Err(err) if err == vk::Result::ERROR_OUT_OF_DATE_KHR => {
							shouldRecreateSwapchain = true;
						},
						Err(err) => { panic!("{err}") },
					}
				}

				let imageIndices = [
					imageIndex,
				];
				let renderFinishedSemaphores = [
					renderFinishedSemaphore,
				];
				let swapchains = [
					swapchain,
				];
				let presentInfo = vk::PresentInfoKHR::builder()
					.swapchains(&swapchains)
					.image_indices(&imageIndices)
					.wait_semaphores(&renderFinishedSemaphores);
				let _isSuboptimalPost = unsafe { swapchainExtension.queue_present(queue, &presentInfo) }.unwrap();
				unsafe {
					let inFlightFences = [
						inFlightFence,
					];
					device.wait_for_fences(&inFlightFences, false, u64::MAX).unwrap();
					device.reset_fences(&inFlightFences).unwrap();
					device.reset_command_pool(commandPool, vk::CommandPoolResetFlags::empty()).unwrap();
				}
			},
			_ => {},
		}
	});
}

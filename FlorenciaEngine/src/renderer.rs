use ash::{
	self,
	vk,
	extensions::{
		ext,
		khr,
	},
};
use winit::{
	event_loop::EventLoop,
	window::{
		WindowBuilder, WindowAttributes
	},
	event::{WindowEvent, Event},
};
use raw_window_handle::{HasRawDisplayHandle, HasRawWindowHandle};

use super::Result;

pub fn test() -> Result<()> {
	let eventLoop = EventLoop::new();
	let window = WindowBuilder::new()
		.with_title("TEST")
		// .with_inner_size(winit::dpi::LogicalSize::new(1920, 1080))
		.with_visible(true)
		.with_resizable(true)
		.build(&eventLoop)?;
	let entry = unsafe { ash::Entry::load() }?;
	let requiredExtensions = ash_window::enumerate_required_extensions(window.raw_display_handle())?;
	let appName = std::ffi::CString::new("App Name")?;
	let engineName = std::ffi::CString::new("Engine Name")?;
	let instance = {
		let applicationInfo = vk::ApplicationInfo::builder()
			.application_name(&appName)
			.application_version(0)
			.engine_name(&engineName)
			.engine_version(0)
			.api_version(vk::API_VERSION_1_3);
		let instanceCreateInfo = vk::InstanceCreateInfo::builder()
			.application_info(&applicationInfo)
			.enabled_extension_names(requiredExtensions);
		// .enabled_layer_names(&layerNamesRaw);
		unsafe { entry.create_instance(&instanceCreateInfo, None) }?
	};
	let physicalDevice = unsafe { instance.enumerate_physical_devices() }?[0];
	let deviceQueuePriorities = [
		1.0,
	];
	let deviceExtensionNames = [
		khr::Swapchain::name().as_ptr(),
	];
	let device = {
		let deviceQueueCreateInfos = [
			vk::DeviceQueueCreateInfo::builder()
				.queue_family_index(0)
				.queue_priorities(&deviceQueuePriorities)
				.build(),
		];
		let deviceCreateInfo = vk::DeviceCreateInfo::builder()
			.queue_create_infos(&deviceQueueCreateInfos)
			.enabled_extension_names(&deviceExtensionNames);
		unsafe { instance.create_device(physicalDevice, &deviceCreateInfo, None) }?
	};
	let queue = unsafe { device.get_device_queue(0, 0) };
	let surfaceExtension = khr::Surface::new(&entry, &instance);
	let surface = unsafe {
		ash_window::create_surface(&entry, &instance, window.raw_display_handle(), window.raw_window_handle(), None)
	}?;
	let swapchainExtension = khr::Swapchain::new(&instance, &device);
	let queueFamilyIndices = [
		0,
	];
	let swapchain = {
		let surfaceCapabilities = unsafe { surfaceExtension.get_physical_device_surface_capabilities(physicalDevice, surface) }?;
		let surfaceFormats = unsafe { surfaceExtension.get_physical_device_surface_formats(physicalDevice, surface) }?;
		let swapchainCreateInfo = vk::SwapchainCreateInfoKHR::builder()
			.surface(surface)
			.clipped(true)
			.composite_alpha(vk::CompositeAlphaFlagsKHR::OPAQUE)
			.image_array_layers(1)
			.image_color_space(vk::ColorSpaceKHR::SRGB_NONLINEAR)
			.image_format(vk::Format::B8G8R8A8_UNORM)
			.image_sharing_mode(vk::SharingMode::EXCLUSIVE)
			.min_image_count(surfaceCapabilities.min_image_count + 1)
			.pre_transform(surfaceCapabilities.current_transform)
			.image_extent(surfaceCapabilities.max_image_extent)
			.image_usage(vk::ImageUsageFlags::TRANSFER_DST)
			.present_mode(vk::PresentModeKHR::FIFO)
			.queue_family_indices(&queueFamilyIndices);

		unsafe { swapchainExtension.create_swapchain(&swapchainCreateInfo, None) }?
	};
	let swapchains = [
		swapchain,
	];
	let swapchainImages = unsafe { swapchainExtension.get_swapchain_images(swapchain) }?;
	let imageSubresourceRange = vk::ImageSubresourceRange::builder()
		.aspect_mask(vk::ImageAspectFlags::COLOR)
		.level_count(1)
		.layer_count(1)
		.build();
	let imageSubresourceRanges = [
		imageSubresourceRange,
	];
	let swapchainImageViews = swapchainImages.iter().copied().map(|image| {
		let imageViewCreateInfo = vk::ImageViewCreateInfo::builder()
			.view_type(vk::ImageViewType::TYPE_2D)
			.format(vk::Format::B8G8R8A8_UNORM)
			.subresource_range(imageSubresourceRange)
			.image(image);
		match unsafe { device.create_image_view(&imageViewCreateInfo, None) } {
			Ok(imageView) => imageView,
			Err(_) => panic!("Unable to create image views"),
		}
	}).collect::<Vec<_>>();
	let semaphore = {
		let semaphoreCreateInfo = vk::SemaphoreCreateInfo::builder();
		unsafe { device.create_semaphore(&semaphoreCreateInfo, None) }?
	};
	let semaphores = [
		semaphore,
	];
	let semaphore2 = {
		let semaphoreCreateInfo = vk::SemaphoreCreateInfo::builder();
		unsafe { device.create_semaphore(&semaphoreCreateInfo, None) }?
	};
	let semaphores2 = [
		semaphore2,
	];
	let fence = {
		let fenceCreateInfo = vk::FenceCreateInfo::builder();
		unsafe { device.create_fence(&fenceCreateInfo, None) }?
	};
	let fences = [
		fence,
	];
	let commandPool = {
		let commandPoolCreateInfo = vk::CommandPoolCreateInfo::builder()
			// .flags(vk::CommandPoolCreateFlags::RESET_COMMAND_BUFFER)
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
	let commandBuffers = [
		commandBuffer,
	];
	eventLoop.run(move |event, window_target, controlflow| {
		match event {
			Event::WindowEvent { event, window_id } => match event {
				WindowEvent::CloseRequested => { controlflow.set_exit() },
				_ => {},
			},
			Event::MainEventsCleared => window.request_redraw(),
			Event::RedrawRequested(id) => {
				let (imageIndex, _isSuboptimal) = unsafe {
					swapchainExtension.acquire_next_image(swapchain, u64::MAX, semaphore, vk::Fence::null())
				}.unwrap();
				let imageIndices = [
					imageIndex,
				];

				let commandBufferBeginInfo = vk::CommandBufferBeginInfo::builder();
				let clearColor = vk::ClearColorValue { float32: [1.0, 0.0, 1.0, 1.0] };
				let submitInfo = vk::SubmitInfo::builder()
					.wait_semaphores(&semaphores)
					.signal_semaphores(&semaphores2)
					.command_buffers(&commandBuffers)
					.build();
				let submitInfos = [
					submitInfo,
				];
				unsafe {
					device.begin_command_buffer(commandBuffer, &commandBufferBeginInfo).unwrap();
					device.cmd_clear_color_image(commandBuffer, swapchainImages[imageIndex as usize], vk::ImageLayout::TRANSFER_DST_OPTIMAL, &clearColor, &imageSubresourceRanges);
					device.end_command_buffer(commandBuffer).unwrap();
					device.queue_submit(queue, &submitInfos, fence).unwrap();
				}

				let presentInfo = vk::PresentInfoKHR::builder()
					.swapchains(&swapchains)
					.image_indices(&imageIndices)
					.wait_semaphores(&semaphores2);
				let _isSuboptimalPost = unsafe { swapchainExtension.queue_present(queue, &presentInfo) }.unwrap();
				unsafe {
					device.wait_for_fences(&fences, false, u64::MAX).unwrap();
					device.reset_fences(&fences).unwrap();
				}
			},
			_ => {},
		}
	});
}

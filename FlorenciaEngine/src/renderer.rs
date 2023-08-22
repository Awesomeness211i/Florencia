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
	window::{Window, WindowBuilder},
};

use super::Result;

unsafe extern "system" fn vulkanDebugUtilsCallback(message_severity: vk::DebugUtilsMessageSeverityFlagsEXT, message_type: vk::DebugUtilsMessageTypeFlagsEXT, p_callback_data: *const vk::DebugUtilsMessengerCallbackDataEXT, _p_user_data: *mut std::ffi::c_void) -> vk::Bool32 {
	let message = std::ffi::CStr::from_ptr((*p_callback_data).p_message);
	let severity = format!("{:?}", message_severity).to_lowercase();
	let ty = format!("{:?}", message_type).to_lowercase();
	println!("[Debug][{}][{}] {:?}", severity, ty, message);
	vk::FALSE
}

pub fn test() -> Result<()> {
	let eventLoop = EventLoop::new();
	let window = WindowBuilder::new()
		.with_title("TEST")
		.with_inner_size(winit::dpi::LogicalSize::new(1920, 1080))
		.build(&eventLoop)?;
	let layerNames = [
		std::ffi::CString::new("VK_LAYER_KHRONOS_validation")?,
	];
	let layerNamesRaw: Vec<_> = layerNames.iter().map(|raw| { raw.as_ptr() }).collect();
	let mut extensions = vec![
		ext::DebugUtils::name().as_ptr(),
		khr::Surface::name().as_ptr(),
	];
	// for extensionName in ash_window::enumerate_required_extensions(&window)? {
	// 	extensions.push(extensionName.as_ptr());
	// }

	let entry = unsafe { ash::Entry::load() }?;
	let appName = std::ffi::CString::new("App Name")?;
	let engineName = std::ffi::CString::new("Engine Name")?;
	let applicationInfo = vk::ApplicationInfo::builder()
		.application_name(&appName)
		.application_version(0)
		.engine_name(&engineName)
		.engine_version(0)
		.api_version(vk::API_VERSION_1_3);
	let instanceCreateInfo = vk::InstanceCreateInfo::builder()
		.application_info(&applicationInfo)
		.enabled_layer_names(&layerNamesRaw);
	let instance = unsafe { entry.create_instance(&instanceCreateInfo, None) }?;

	// let surface = unsafe {
	// 	ash_window::create_surface(&entry, &instance, &window, &window, None)
	// }?;
	let surfaceLoader = khr::Surface::new(&entry, &instance);

	let debugUtils = ext::DebugUtils::new(&entry, &instance);
	let debugInfo = vk::DebugUtilsMessengerCreateInfoEXT::builder()
		.message_severity(vk::DebugUtilsMessageSeverityFlagsEXT::ERROR | vk::DebugUtilsMessageSeverityFlagsEXT::WARNING | vk::DebugUtilsMessageSeverityFlagsEXT::INFO | vk::DebugUtilsMessageSeverityFlagsEXT::VERBOSE)
		.message_type(vk::DebugUtilsMessageTypeFlagsEXT::GENERAL | vk::DebugUtilsMessageTypeFlagsEXT::VALIDATION | vk::DebugUtilsMessageTypeFlagsEXT::PERFORMANCE)
		.pfn_user_callback(Some(vulkanDebugUtilsCallback));
	// let debugMessenger = unsafe {
	// 	debugUtils.create_debug_utils_messenger(&debugInfo, None)
	// }?;

	let physicalDevice = unsafe { instance.enumerate_physical_devices() }?[0];
	
	// let formats = unsafe { surfaceLoader.get_physical_device_surface_formats(physicalDevice, surface) };

	let queueFamilyProperties = unsafe { instance.get_physical_device_queue_family_properties(physicalDevice) };

	let deviceQueuePriorities = [
		1.0,
	];
	let deviceQueueCreateInfos = [
		vk::DeviceQueueCreateInfo::builder()
			.queue_family_index(0)
			.queue_priorities(&deviceQueuePriorities)
			.build(),
	];
	let deviceCreateInfo = vk::DeviceCreateInfo::builder().queue_create_infos(&deviceQueueCreateInfos);
	let device = unsafe { instance.create_device(physicalDevice, &deviceCreateInfo, None) }?;
	let commandPoolCreateInfo = vk::CommandPoolCreateInfo::builder().queue_family_index(0);
	let commandPool = unsafe { device.create_command_pool(&commandPoolCreateInfo, None) }?;
	let commandBufferAllocateInfo = vk::CommandBufferAllocateInfo::builder()
		.command_pool(commandPool)
		.level(vk::CommandBufferLevel::PRIMARY)
		.command_buffer_count(1);
	let commandBuffers = unsafe { device.allocate_command_buffers(&commandBufferAllocateInfo) }?;
	Ok(())
}

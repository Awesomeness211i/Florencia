use ash::{
	self,
	vk,
};
use winit::{
	event_loop::EventLoop,
	window::WindowBuilder,
};

use super::Result;

pub fn test() -> Result<()> {
	let eventLoop = EventLoop::new();
	let window = WindowBuilder::new().with_title("TEST").with_inner_size(winit::dpi::LogicalSize::new(1920, 1080)).build(&eventLoop)?;
	let entry = unsafe { ash::Entry::load() }?;
	let appName = unsafe { std::ffi::CStr::from_bytes_with_nul_unchecked(b"TEST\0") };
	let layerNames = [
		unsafe { std::ffi::CStr::from_bytes_with_nul_unchecked(b"VK_LAYER_KHRONOS_validation\0") },
	];
	let layerNamesRaw: Vec<_> = layerNames.iter().map(|raw| { raw.as_ptr() }).collect();
	let applicationInfo = vk::ApplicationInfo {
		s_type: vk::StructureType::APPLICATION_INFO,
		p_next: std::ptr::null(),
		p_application_name: std::ptr::null(),
		application_version: 0,
		p_engine_name: std::ptr::null(),
		engine_version: 0,
		api_version: vk::API_VERSION_1_3,
	};
	let instanceCreateInfo = vk::InstanceCreateInfo::builder()
		.application_info(&applicationInfo)
		.enabled_layer_names(&layerNamesRaw);
	let instance = unsafe { entry.create_instance(&instanceCreateInfo, None) }?;
	let debugInfo = vk::DebugUtilsMessengerCreateInfoEXT::builder()
		.message_severity(vk::DebugUtilsMessageSeverityFlagsEXT::ERROR | vk::DebugUtilsMessageSeverityFlagsEXT::WARNING | vk::DebugUtilsMessageSeverityFlagsEXT::INFO)
		.message_type(vk::DebugUtilsMessageTypeFlagsEXT::GENERAL | vk::DebugUtilsMessageTypeFlagsEXT::VALIDATION | vk::DebugUtilsMessageTypeFlagsEXT::PERFORMANCE);
	let physicalDevice = unsafe { instance.enumerate_physical_devices() }?[0];
	let queueFamilyProperties = unsafe { instance.get_physical_device_queue_family_properties(physicalDevice) };
	let deviceCreateInfo = vk::DeviceCreateInfo {
		s_type: vk::StructureType::DEVICE_CREATE_INFO,
		p_next: std::ptr::null(),
		flags: vk::DeviceCreateFlags::default(),
		queue_create_info_count: 0,
		p_queue_create_infos: std::ptr::null(),
		enabled_extension_count: 0,
		pp_enabled_extension_names: std::ptr::null(),
		p_enabled_features: std::ptr::null(),
		/* This done to avoid implementing deprecated options and also warnings that come with that */
		..Default::default()
	};
	let device = unsafe { instance.create_device(physicalDevice, &deviceCreateInfo, None) }?;
	let commandPoolCreateInfo = vk::CommandPoolCreateInfo {
		s_type: vk::StructureType::COMMAND_POOL_CREATE_INFO,
		p_next: std::ptr::null(),
		flags: vk::CommandPoolCreateFlags::default(),
		queue_family_index: 0,
	};
	let commandPool = unsafe { device.create_command_pool(&commandPoolCreateInfo, None) }?;
	let commandBufferAllocateInfo = vk::CommandBufferAllocateInfo {
		s_type: vk::StructureType::COMMAND_BUFFER_ALLOCATE_INFO,
		p_next: std::ptr::null(),
		command_pool: commandPool,
		level: vk::CommandBufferLevel::PRIMARY,
		command_buffer_count: 0,
	};
	let commandBuffers = unsafe { device.allocate_command_buffers(&commandBufferAllocateInfo) }?;
	Ok(())
}

pub struct Instance {
	entry: ash::Entry,
	instance: ash::Instance,
	allocationCallbacks: Option<vk::AllocationCallbacks>,
}

pub struct InstanceInfo {
	appInfo: vk::ApplicationInfo,
	extensions: Vec<std::ffi::CString>,
	extensionPointers: Vec<*const i8>,
	instanceInfo: vk::InstanceCreateInfo,
	allocationCallbacks: Option<vk::AllocationCallbacks>,
}

impl InstanceInfo {
	pub fn new(requiredExtensions: Vec<String>, allocationCallbacks: Option<vk::AllocationCallbacks>) -> Self {
		let appInfo = vk::ApplicationInfo {
			s_type: vk::StructureType::APPLICATION_INFO,
			p_next: std::ptr::null(),
			p_application_name: std::ptr::null(),
			application_version: 0,
			p_engine_name: std::ptr::null(),
			engine_version: 0,
			api_version: vk::API_VERSION_1_3,
		};
		let extensions: Vec<_> = requiredExtensions.iter().map(|ext| { std::ffi::CString::new(ext.clone()).expect("Failed to convert extension name") }).collect();
		let extensionPointers: Vec<_> = extensions.iter().map(|ext| { ext.as_ptr() }).collect();
		let instanceInfo = vk::InstanceCreateInfo {
			s_type: vk::StructureType::INSTANCE_CREATE_INFO,
			p_next: std::ptr::null(),
			flags: vk::InstanceCreateFlags::empty(),
			p_application_info: &appInfo,
			enabled_layer_count: 0,
			pp_enabled_layer_names: std::ptr::null(),
			enabled_extension_count: extensionPointers.len() as _,
			pp_enabled_extension_names: extensionPointers.as_ptr(),
		};
		Self {
			appInfo,
			extensions,
			extensionPointers,
			instanceInfo,
			allocationCallbacks,
		}
	}
}

impl Instance {
	pub fn new(entry: ash::Entry, info: InstanceInfo) -> Result<Self> {
		let instance = unsafe { entry.create_instance(&info.instanceInfo, info.allocationCallbacks.as_ref()) }?;
		Ok(Self {
			entry,
			instance,
			allocationCallbacks: info.allocationCallbacks
		})
	}

	pub fn handle(self: &Self) -> vk::Instance {
		self.instance.handle()
	}

	fn Data(self: &Self) -> (&ash::Instance, &Option<vk::AllocationCallbacks>) {
		(&self.instance, &self.allocationCallbacks)
	}
}

impl Drop for Instance {
	fn drop(self: &mut Self) {
		unsafe { self.instance.destroy_instance(self.allocationCallbacks.as_ref()) };
	}
}

pub struct PhysicalDevicePool {
	pool: Vec<vk::PhysicalDevice>,
}

impl PhysicalDevicePool {
	fn new(instance: &Instance) -> Result<Self> {
		let (i, _) = instance.Data();
		Ok(Self {
			pool: unsafe { i.enumerate_physical_devices() }?,
		})
	}
}

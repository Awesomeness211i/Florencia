use ash::{self, vk};

use super::{
	Result,
};

fn test() {
	/*let entry = unsafe { ash::Entry::load() }?;

	let deviceCreateInfo = vk::DeviceCreateInfo::builder();
	let device = unsafe { instance.create_device(physicalDevice, &deviceCreateInfo, None) }?;*/
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
			instanceInfo,
			allocationCallbacks,
			extensions,
			extensionPointers,
		}
	}
}

impl Instance {
	pub fn new(entry: ash::Entry, info: InstanceInfo) -> Result<Self> {
		let instance = unsafe { entry.create_instance(&info.instanceInfo, info.allocationCallbacks.as_ref()) }?;
		Ok(Self { entry, instance, allocationCallbacks: info.allocationCallbacks })
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


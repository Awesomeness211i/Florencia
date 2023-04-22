/*use ash::{self, vk};

fn test() {
	let entry = unsafe { ash::Entry::load() }?;
	let applicationInfo = vk::ApplicationInfo::builder().api_version(vk::API_VERSION_1_3);
	let instanceCreateInfo = vk::InstanceCreateInfo::builder().application_info(&applicationInfo);
	let instance = unsafe { entry.create_instance(&instanceCreateInfo, None) }?;

	let physicalDevice = unsafe { instance.enumerate_physical_devices() }?.into_iter().next()?;
	let deviceCreateInfo = vk::DeviceCreateInfo::builder();
	let device = unsafe { instance.create_device(physicalDevice, &deviceCreateInfo, None) }?;

	unsafe { instance.destroy_instance(None) }
}*/
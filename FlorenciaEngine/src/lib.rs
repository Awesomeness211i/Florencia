#![allow(non_snake_case)]

//! # FlorenciaEngine
//! This is a set of functions and data structures made specifically for
//! the purpose of making developing games and applications easier

pub mod event;
pub mod layer;
pub mod window;
pub mod application;

pub use event::Event;
pub use layer::Layer;
pub use layer::LayerStack;

pub use window::Window;
pub use window::WindowData;
pub use application::Application;

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
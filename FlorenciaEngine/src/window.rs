use std::{
	sync::mpsc,
};

use winit::{
	event::{Event, WindowEvent},
	event_loop::{EventLoop, ControlFlow},
	window::{WindowBuilder},
};

use super::{
	Result,
	renderer,
};

pub struct WindowData {
	pub vsync: bool,
	pub polling: bool,

	pub title: String,
	pub dimensions: (u32, u32),
}

/**
This is a wrapper over data needed for using glfw
*/
pub struct Window {
	window: winit::window::Window,
	eventLoop: winit::event_loop::EventLoop<()>,
}

impl Window {
	/**
	This function is used for construction of a glfw window
	This takes a type that abstracts over the needed parameters and options that glfw gives
	*/
	pub fn new(data: WindowData) -> Result<Self> {
		let eventLoop = EventLoop::new();
		let window = WindowBuilder::new().with_title(data.title).with_inner_size(winit::dpi::LogicalSize::new(data.dimensions.0, data.dimensions.1)).build(&eventLoop)?;

		// let entry = ash::Entry::load()?;
		// let instance = renderer::Instance::new(entry, info)?;
		Ok(Window{
			window,
			eventLoop,
		})
	}

	pub fn GetSize(&self) -> (i32, i32) {
		(0, 0)
	}
	
	pub fn Update(&mut self) {
	}
}

use std::{
	sync::mpsc,
};

use glfw::{
	Key,
	Action,
	Context,
	WindowEvent
};

use super::{
	Result,
	renderer,
};

pub struct WindowData {
	pub m_Vsync: bool,
	pub m_Polling: bool,

	pub m_Title: String,
	pub m_Dimensions: (u32, u32),
}

/**
This is a wrapper over data needed for using glfw
*/
pub struct Window {
	m_Instance: glfw::Glfw,
	m_Window: glfw::Window,
	//m_Sender: mpsc::Sender<()>,
	m_Events: mpsc::Receiver<(f64,WindowEvent)>,
}

impl Window {
	/**
	This function is used for construction of a glfw window
	This takes a type that abstracts over the needed parameters and options that glfw gives
	*/
	pub fn new(data: WindowData) -> Result<Self> {
		let mut glfw = glfw::init(glfw::FAIL_ON_ERRORS)?;

		glfw.window_hint(glfw::WindowHint::Visible(true));
		glfw.window_hint(glfw::WindowHint::ClientApi(glfw::ClientApiHint::NoApi));

		let (mut window, events) = glfw.create_window(data.m_Dimensions.0, data.m_Dimensions.1, data.m_Title.as_str(), glfw::WindowMode::Windowed).expect("Failed to create GLFW window.");

		window.set_all_polling(data.m_Polling);

		/*
		let mut renderContext = window.render_context();
		let (send, recieve) = mpsc::channel();
		let renderTask = Builder::new().name("render task".to_string());
		let renderTaskDone = renderTask.spawn(move || {
			renderContext.make_current();
			loop {
				if recieve.try_recv() == Ok(()) {
					break;
				};

				//Rendering Calls

				renderContext.swap_buffers();
			}
			glfw::make_context_current(None);
		});
		*/

		assert!(glfw.vulkan_supported());
		let entry = unsafe { ash::Entry::load() }?;

		let requiredExtensions = glfw.get_required_instance_extensions().unwrap_or(vec![]);
		println!("Vulkan required extensions: {:?}", requiredExtensions);
		let info = renderer::InstanceInfo::new(requiredExtensions, None);
		let instance = renderer::Instance::new(entry, info)?;

		let mut surface = std::mem::MaybeUninit::uninit();
		if window.create_window_surface(instance.handle(), std::ptr::null(), surface.as_mut_ptr()) != ash::vk::Result::SUCCESS {
			panic!("Failed to create a GLFW window surface");
		}

		Ok(Window{
			m_Instance: glfw,
			m_Window: window,
			//m_Sender: send,
			m_Events: events,
		})
	}
	
	/**
	Returns from glfw if the window should close
	*/
	pub fn ShouldClose(self: &Self) -> bool {
		self.m_Window.should_close()
	}

	pub fn GetSize(self: &Self) -> (i32, i32) {
		self.m_Window.get_size()
	}
	
	pub fn Update(self: &mut Self) {
		self.m_Instance.poll_events();
		for (_, event) in glfw::flush_messages(&self.m_Events) {
			match event {
				glfw::WindowEvent::Key(Key::Escape, _, Action::Press, _) => {
					self.m_Window.set_should_close(true);
				}
				_ => {}
			}
		}
	}

	/*pub fn temp(self: &Self) {
		self.m_Sender.send(()).unwrap();
	}*/
}

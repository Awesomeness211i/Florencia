use std::sync::mpsc;
use glfw::{Action, Context, Key, WindowEvent};

pub struct WindowData {
	pub m_Vsync: bool,
	pub m_Polling: bool,

	pub m_Title: String,
	pub m_Dimensions: (u32, u32),
}

///This is a wrapper over data needed for using glfw
pub struct Window {
	m_Instance: glfw::Glfw,
	m_Window: glfw::Window,
	m_Events: mpsc::Receiver<(f64,WindowEvent)>,
}

impl Window {
	///This function is used for construction of a glfw window
	///This takes a type that abstracts over the needed parameters and options that glfw gives
	pub fn Create(data: WindowData) -> Self {
		let mut glfw = glfw::init(glfw::FAIL_ON_ERRORS).unwrap();
		let (mut window, events)
		= glfw.create_window(data.m_Dimensions.0, data.m_Dimensions.1, data.m_Title.as_str(), glfw::WindowMode::Windowed).expect("Failed to create GLFW window.");
		window.make_current();
		window.set_all_polling(data.m_Polling);
		window.show();
		Window{
			m_Instance: glfw,
			m_Window: window,
			m_Events: events
		}
	}
	
	///Returns from glfw if the window should close
	pub fn ShouldClose(self: &Self) -> bool {
		self.m_Window.should_close()
	}

	pub fn GetSize(self: &Self) -> (i32, i32) {
		self.m_Window.get_size()
	}
	
	pub fn Update(self: &mut Self) {
		self.m_Instance.poll_events();
		self.m_Window.swap_buffers();
		for (_, _event) in glfw::flush_messages(&self.m_Events) {
			/*match event {
				glfw::WindowEvent::Key(Key::Escape, _, Action::Press, _) => {
					self.m_Window.set_should_close(true);
				}
				_ => {}
			}*/
		}
	}
}
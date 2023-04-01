use std::sync::mpsc;
use glfw::{Action, Context, Key, WindowEvent};

pub enum WindowData {
	TITLE(String),
	WIDTH(u32),
	HEIGHT(u32),
}

pub struct Window {
	m_Instance: glfw::Glfw,
	m_Window: glfw::Window,
	m_Events: mpsc::Receiver<(f64,WindowEvent)>,
}

impl Window {
	pub fn Create(name: &str, width: u32, height: u32) -> Self {
		let mut glfw = glfw::init(glfw::FAIL_ON_ERRORS).unwrap();
		let (mut window, events)
		= glfw.create_window(width, height, name, glfw::WindowMode::Windowed).expect("Failed to create GLFW window.");
		window.make_current();
		window.set_key_polling(true);
		Window{
			m_Instance: glfw,
			m_Window: window,
			m_Events: events
		}
	}
	
	pub fn IsOpen(self: &Self) -> bool {
		!self.m_Window.should_close()
	}
	
	pub fn SwapBuffers(self: &mut Self) {
		self.m_Window.swap_buffers();
	}
	
	pub fn Update(self: &mut Self) {
		self.m_Instance.poll_events();
		for (_, event) in glfw::flush_messages(&self.m_Events) {
			match event {
				glfw::WindowEvent::Key(Key::Escape, _, Action::Press, _) => {
					self.m_Window.set_should_close(true);
				}
				_ => {},
			}
		}
	}
}
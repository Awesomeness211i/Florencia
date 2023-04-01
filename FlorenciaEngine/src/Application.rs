use super::Window;

pub struct Application {
	m_Running: bool,
	m_Window: Option<Window::Window>,
	m_CommandLineArgs: Vec<String>,
}

impl Application {
	pub fn Create(window: Option<Window::Window>) -> Self {
		let args: Vec<_> = std::env::args().collect();
		Application{
			m_Running: true,
			m_Window: window,
			m_CommandLineArgs: args
		}
	}
	
	pub fn Run(self: &mut Self) {
		while self.m_Running {
			match &mut self.m_Window {
				Some(ref mut win) => {
					win.Update();
					win.SwapBuffers();
					self.m_Running = win.IsOpen();
				}
				None => {
					
				}
			}
		}
	}

	fn Close(self: &mut Self) {
		self.m_Running = false;
	}
}
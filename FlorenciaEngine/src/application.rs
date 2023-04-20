use super::{
	Window,
	WindowData,
	LayerStack,
};

pub struct Application {
	pub m_Window: Option<Window>,

	m_Running: bool,
	m_Minimized: bool,
	m_LayerStack: LayerStack,
}

impl Application {
	pub fn new(window: Option<Window>) -> Self {
		return Self {
			m_Window: window,
            m_Running: true,
			m_Minimized: false,
            m_LayerStack: LayerStack::new(),
		};
	}
	pub fn Run(self: &mut Self) {
		while self.m_Running {
			if let Some(window) = self.m_Window.as_mut() {
                window.Update();
				window.SwapBuffers();
				self.m_Running = !window.ShouldClose();
            }
		}
	}
}
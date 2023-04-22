use super::{
	Layer,
	window,
	WindowData,
	LayerStack,
};

pub struct ApplicationConfig {
	pub windowData: WindowData,
	pub commandLineArgs: Vec<String>,
	pub workingDirectory: std::path::PathBuf,
}

pub struct Application {
	m_Running: bool,
	m_Minimized: bool,

	m_Window: window::Window,
	m_LayerStack: LayerStack,
}

pub trait ApplicationEngine {
	fn new() -> Self;
	fn Get(self: &mut Self) -> &mut Application;
	fn Run(self: &mut Self) { self.Get().Run(); }
}

impl Application {
	pub fn new(appData: ApplicationConfig) -> Self {
		//println!("Current Dir: {:#?}", appData.workingDirectory);
		return Self {
			m_Window: window::Window::Create(appData.windowData),
			m_Running: true,
			m_Minimized: true,
			m_LayerStack: LayerStack::new(),
		};
	}
	pub fn AddLayer(self: &mut Self, layer: Box<dyn Layer>) {
		self.m_LayerStack.AddLayer(layer);
	}
	pub fn AddOverlay(self: &mut Self, overlay: Box<dyn Layer>) {
		self.m_LayerStack.AddOverlay(overlay);
	}
	pub fn RemoveLayer(self: &mut Self, uuid: u64) {
        self.m_LayerStack.RemoveLayer(uuid);
    }
	pub fn RemoveOverlay(self: &mut Self, uuid: u64) {
        self.m_LayerStack.RemoveOverlay(uuid);
    }
	pub fn Close(self: &mut Self) {
		self.m_Running = false;
	}
	pub fn Run(self: &mut Self) {
		while self.m_Running {
			if !self.m_Minimized {
				for layer in self.m_LayerStack.iter() {
					layer.Update(1.0);
					layer.Render();
				}
			}
			self.m_Window.Update();
			self.m_Running = !self.m_Window.ShouldClose();
		}
		/*
		for (index, value) in v.iter().enumerate() {
			println!("{} is at index {}", value, index);
		}
		*/
	}
}
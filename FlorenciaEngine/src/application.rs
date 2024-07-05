use super::{
	Layer,
	Result,
	WindowData,
	LayerStack,
};

pub trait ApplicationEngine {
	fn new() -> Result<Self> where Self: Sized;
	fn Get(&mut self) -> &mut Application;
	fn Run(&mut self) -> Result<()> { self.Get().Run() }
}

pub struct ApplicationConfig {
	pub windowData: Option<WindowData>,
	pub commandLineArgs: Vec<String>,
	pub workingDirectory: std::path::PathBuf,
}

pub struct Application {
	pub commandLineArgs: Vec<String>,
	pub workingDirectory: std::path::PathBuf,

	running: bool,

	layerStack: LayerStack,
	instant: std::time::Instant,
}

impl Application {
	pub fn new(appData: ApplicationConfig) -> Result<Self> {
		match appData.windowData {
			Some(_data) => {
				Ok(Self {
					running: true,
					commandLineArgs: appData.commandLineArgs,
					workingDirectory: appData.workingDirectory,

					layerStack: LayerStack::default(),
					instant: std::time::Instant::now(),
				})
			},
			None => {
				Ok(Self {
					running: true,
					commandLineArgs: appData.commandLineArgs,
					workingDirectory: appData.workingDirectory,

					layerStack: LayerStack::default(),
					instant: std::time::Instant::now(),
				})
			},
		}
	}

	pub fn AddLayer(&mut self, layer: Box<dyn Layer>) {
		self.layerStack.AddLayer(layer);
	}

	pub fn AddOverlay(&mut self, overlay: Box<dyn Layer>) {
		self.layerStack.AddOverlay(overlay);
	}

	pub fn RemoveLayer(&mut self, uuid: u64) {
		self.layerStack.RemoveLayer(uuid);
	}

	pub fn RemoveOverlay(&mut self, uuid: u64) {
		self.layerStack.RemoveOverlay(uuid);
	}

	pub fn Close(&mut self) {
		self.running = false;
	}

	pub fn Run(&mut self) -> Result<()> {
		while self.running {
		}
		Ok(())
	}
}

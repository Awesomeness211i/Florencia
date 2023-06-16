use super::{
	Layer,
	Result,
	window,
	WindowData,
	LayerStack,
};

/**
This trait is implemented by all types that can be used as an application
generally you should only have one of these types but there could be other
use cases I didn't think of.
*/
pub trait ApplicationEngine {
	fn new() -> Result<Self> where Self: Sized;
	fn Get(self: &mut Self) -> &mut Application;
	fn Run(self: &mut Self) -> Result<()> { self.Get().Run() }
}

/**
Configuration information for the `Application` type.
*/
pub struct ApplicationConfig {
	pub windowData: WindowData,
	pub commandLineArgs: Vec<String>,
	pub workingDirectory: std::path::PathBuf,
}

/**
Your application type needs to own one of these types to
interface with the rest of the library.

Example:
```
use FlorenciaEngine::Application;

struct Type {
	application: Application
}
```

The `Get()` method is used in the library to implement the `Run()` method
on your type automatically. So please don't implement the `Run()` method yourself.

You create an instance of `Application` by calling
`Application::new()` with an `ApplicationConfig`.

Example:
```
use FlorenciaEngine::{WindowData, ApplicationConfig, ApplicationEngine, Application};

impl ApplicationEngine for Type {
	fn new() -> Result<Self> {
		let windowData = WindowData {
			...
		};
		let appConfig = ApplicationConfig {
			windowData: windowData,
			...
		};
		return Self {
			application: Application::new(appConfig),
		};
	}
}
```
*/
pub struct Application {
	pub commandLineArgs: Vec<String>,
	pub workingDirectory: std::path::PathBuf,

	running: bool,
	minimized: bool,

	window: window::Window,
	layerStack: LayerStack,
	instant: std::time::Instant,
}

impl Application {
	pub fn new(appData: ApplicationConfig) -> Result<Self> {
		return Ok(Self {
			running: true,
			commandLineArgs: appData.commandLineArgs,
			workingDirectory: appData.workingDirectory,
			minimized: false,
			// minimized: appData.windowData.m_Dimensions.0 == 0 || appData.windowData.m_Dimensions.1 == 0,

			layerStack: LayerStack::new(),
			instant: std::time::Instant::now(),
			window: window::Window::new(appData.windowData)?,
		});
	}

	pub fn AddLayer(self: &mut Self, layer: Box<dyn Layer>) {
		self.layerStack.AddLayer(layer);
	}

	pub fn AddOverlay(self: &mut Self, overlay: Box<dyn Layer>) {
		self.layerStack.AddOverlay(overlay);
	}

	pub fn RemoveLayer(self: &mut Self, uuid: u64) {
		self.layerStack.RemoveLayer(uuid);
	}

	pub fn RemoveOverlay(self: &mut Self, uuid: u64) {
		self.layerStack.RemoveOverlay(uuid);
	}

	pub fn Close(self: &mut Self) {
		self.running = false;
	}

	pub fn Run(self: &mut Self) -> Result<()> {
		while self.running {
			let ts = self.instant.elapsed();
			if !self.minimized {
				for layer in self.layerStack.iter() {
					layer.Update(ts);
					layer.Render();
				}
			}
			// self.window.Update();
			// self.running = !self.m_Window.ShouldClose();
			self.instant = std::time::Instant::now();
		}
		return Ok(());
		/*
		for (index, value) in v.iter().enumerate() {
			println!("{} is at index {}", value, index);
		}
		*/
	}
}

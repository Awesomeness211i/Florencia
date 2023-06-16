use FlorenciaEngine::*;
use super::{
	Result,
	editor,
};

pub struct FloEditor {
	application: Application,
}

impl ApplicationEngine for FloEditor {
	fn Get(self: &mut Self) -> &mut Application { return &mut self.application; }
	fn new() -> Result<Self> {
		let windowData = WindowData {
			title: String::from("FloEditor"),
			dimensions: (800, 400),
			polling: true,
			vsync: false,
		};
		let appConfig = ApplicationConfig {
			windowData,
			commandLineArgs: std::env::args().collect(),
			workingDirectory: std::env::current_dir()?,
		};
		let mut application = Application::new(appConfig)?;
		let layer = editor::EditorLayer::new();
		application.AddLayer(layer);
		return Ok(Self {
			application,
		});
	}
}

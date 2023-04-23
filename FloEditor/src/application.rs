use FlorenciaEngine::*;
use super::editor;

pub struct FloEditor {
	application: Application,
}

impl ApplicationEngine for FloEditor {
	fn Get(self: &mut Self) -> &mut Application { return &mut self.application; }
	fn new() -> Self {
		let windowData = WindowData {
			m_Title: String::from("FloEditor"),
			m_Dimensions: (800, 400),
			m_Polling: true,
			m_Vsync: false,
		};
		let appConfig = ApplicationConfig {
			windowData: windowData,
			commandLineArgs: std::env::args().collect(),
			workingDirectory: std::env::current_dir().unwrap(),
		};
		let mut application = Application::new(appConfig);
		let layer = editor::EditorLayer::new();
		application.AddLayer(layer);
		return Self {
			application: application,
		};
	}
}
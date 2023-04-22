#![allow(bad_style)]

//! # FloEditor
//! This library encompasses the specific behaviors I want
//! in my game engine

use FlorenciaEngine::*;

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
		};
		let appConfig = ApplicationConfig {
			windowData: windowData,
			commandLineArgs: std::env::args().collect(),
			workingDirectory: std::env::current_dir().unwrap(),
		};
		return FloEditor {
			application: Application::new(appConfig),
		};
	}
}
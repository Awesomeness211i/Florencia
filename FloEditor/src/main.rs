#![allow(bad_style)]

use FloEditor::*;
use FlorenciaEngine::*;

fn main() {
	let mut app = Application::new(Some(Window::Create(WindowData {
		m_Title: "FloEditor",
		m_Dimensions: (1280, 720),
		m_Polling: true,
	})));
	app.Run();
}
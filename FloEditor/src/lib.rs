#![allow(non_snake_case)]

//! # FloEditor
//! This library encompasses the specific behaviors I want
//! in my game engine

use FlorenciaEngine::*;

fn new() {
	let args: Vec<String> = std::env::args().collect();
	let data = WindowData {
		m_Dimensions: (800, 400),
		m_Polling: true,
		m_Title: "FloEditor",
	};
	/*Editor {
		m_Running: true,
		m_LayerStack: LayerStack::new(),
		m_Window: Some(Window::Create(data)),
	}*/
}
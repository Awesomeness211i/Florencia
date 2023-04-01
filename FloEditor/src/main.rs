#![allow(non_snake_case)]

use FlorenciaEngine::{
	Application::Application,
	Window::Window
};

fn main() {
	let mut app = Application::Create(Some(Window::Create("FloEditor", 800, 400)));
	app.Run();
}
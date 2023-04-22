#![allow(bad_style, dead_code)]

//! # FlorenciaEngine
//! This is a set of functions and data structures made specifically for
//! the purpose of making developing games and applications easier

mod event;
mod layer;
mod window;
mod renderer;
mod application;

pub use event::Event;
pub use event::KeyEvent;
pub use event::MouseEvent;
pub use event::EventCategory;
pub use event::ApplicationEvent;

pub use layer::Layer;
pub use layer::LayerStack;

pub use window::WindowData;

pub use application::Application;
pub use application::ApplicationEngine;
pub use application::ApplicationConfig;
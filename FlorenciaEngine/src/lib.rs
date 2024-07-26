#![allow(bad_style)]

/*!
# FlorenciaEngine
This is a set of functions and data structures made specifically for
the purpose of making developing games and applications easier for me
*/

mod event;
mod layer;
mod window;
mod renderer;
mod threadpool;
mod application;

use anyhow::Result;

pub use event::Event;
pub use event::EventCategory;
pub use event::keyevent::KeyEvent;
pub use event::mouseevent::MouseEvent;
pub use event::applicationevent::ApplicationEvent;

pub use layer::Layer;
pub use layer::LayerStack;

pub use window::WindowData;

pub use renderer::test;

pub use application::Application;
pub use application::ApplicationEngine;
pub use application::ApplicationConfig;

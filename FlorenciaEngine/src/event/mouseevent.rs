use super::*;

#[derive(Debug)]
pub enum MouseEvent {
	MouseMoved{ x: u64, y: u64 },
	MouseScrolled{ x: u64, y: u64 },
	MousePressed{ mouseButton: u64 },
	MouseReleased{ mouseButton: u64 },
}
impl Event for MouseEvent {
	fn GetName(&self) -> &str {
		match self {
			MouseEvent::MouseMoved{ x: _, y: _ } => "MouseMoved",
			MouseEvent::MouseScrolled{ x: _, y: _ } => "MouseScrolled",
			MouseEvent::MousePressed{ mouseButton: _ } => "MouseClicked",
			MouseEvent::MouseReleased{ mouseButton: _ } => "MouseReleased",
		}
	}
	fn GetEventType(&self) -> EventType {
		match self {
			MouseEvent::MouseMoved{ x: _, y: _ } => EventType::MouseMoved,
			MouseEvent::MouseScrolled{ x: _, y: _ } => EventType::MouseScrolled,
			MouseEvent::MousePressed{ mouseButton: _ } => EventType::MousePressed,
			MouseEvent::MouseReleased{ mouseButton: _ } => EventType::MouseReleased,
		}
	}
	fn GetCategoryFlags(&self) -> u64 {
		match self {
			MouseEvent::MousePressed{ mouseButton: _ } => EventCategory::Input | EventCategory::Mouse | EventCategory::MouseButton,
			MouseEvent::MouseReleased{ mouseButton: _ } => EventCategory::Input | EventCategory::Mouse | EventCategory::MouseButton,
			_ => EventCategory::Input | EventCategory::Mouse,
		}
	}
}

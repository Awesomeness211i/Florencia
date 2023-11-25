use super::*;

#[derive(Debug)]
pub enum KeyEvent {
	KeyPressed{ keyCode: u64, repeatCount: u64 },
	KeyReleased{ keyCode: u64 },
	CharacterTyped{ charCode: u64 },
}
impl Event for KeyEvent {
	fn GetName(&self) -> &str {
		match self {
			KeyEvent::KeyPressed{ keyCode: _, repeatCount: _ } => "KeyPressed",
			KeyEvent::KeyReleased{ keyCode: _ } => "KeyReleased",
			KeyEvent::CharacterTyped{ charCode: _ } => "CharacterTyped",
		}
	}
	fn GetEventType(&self) -> EventType {
		match self {
			KeyEvent::KeyPressed{ keyCode: _, repeatCount: _ } => EventType::KeyPressed,
			KeyEvent::KeyReleased{ keyCode: _ } => EventType::KeyReleased,
			KeyEvent::CharacterTyped{ charCode: _ } => EventType::CharacterTyped,
		}
	}
	fn GetCategoryFlags(&self) -> u64 {
		EventCategory::Input | EventCategory::Keyboard
	}
}

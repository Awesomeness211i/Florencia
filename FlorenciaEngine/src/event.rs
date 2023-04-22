pub trait Event: std::fmt::Debug {
	fn GetName(self: &Self) -> &str;
	fn GetCategoryFlags(self: &Self) -> u64;
	fn GetEventType(self: &Self) -> EventType;
	fn ToString(self: &Self) -> String { String::from(self.GetName()) }
	fn IsInCategory(self: &Self, category: EventCategory) -> u64 { self.GetCategoryFlags() & category as u64 }
}
impl std::fmt::Display for dyn Event {
	fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
		return write!(f, "{:#?}", self);
	}
}

#[derive(Debug)]
pub enum EventType {
	None = 0,
	AppClose, AppResize, AppFocus, AppLostFocus, AppMoved, AppTick, AppUpdate, AppRender,
	KeyPressed, KeyReleased, CharacterTyped,
	MousePressed, MouseReleased, MouseMoved, MouseScrolled
}
impl std::fmt::Display for EventType {
	fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
		return write!(f, "{:#?}", self);
	}
}
pub enum EventCategory {
	None = 0,
	Application = 1,
	Input = 0b10,
	Keyboard = 0b100,
	Mouse = 0b1000,
	MouseButton = 0b10000,
}
impl EventCategory {
	pub fn ToU64(self: Self) -> u64 {
		return self as u64;
	}
}
impl std::ops::BitOr for EventCategory {
	type Output = u64;
	fn bitor(self: Self, rhs: EventCategory) -> Self::Output {
		return self.ToU64() | rhs.ToU64();
	}
}
impl std::ops::BitOr<EventCategory> for u64 {
	type Output = u64;
	fn bitor(self: Self, rhs: EventCategory) -> Self::Output {
		return self | rhs.ToU64();
	}
}
impl std::ops::BitAnd for EventCategory {
	type Output = u64;
	fn bitand(self, rhs: EventCategory) -> Self::Output {
		return self.ToU64() & rhs;
	}
}
impl std::ops::BitAnd<EventCategory> for u64 {
	type Output = u64;
	fn bitand(self, rhs: EventCategory) -> Self::Output {
		return self & rhs.ToU64();
	}
}

#[derive(Debug)]
pub enum ApplicationEvent {
	Resize{ width: u32, height: u32 },
	Update,
	Render,
	Close,
	Tick,
}
impl Event for ApplicationEvent {
	fn GetName(self: &Self) -> &str {
		return match self {
			ApplicationEvent::Resize{ width: _, height: _ } => "AppResize",
			ApplicationEvent::Update => "AppUpdate",
			ApplicationEvent::Render => "AppRender",
			ApplicationEvent::Close => "AppClose",
			ApplicationEvent::Tick => "AppTick",
		};
	}
	fn GetEventType(self: &Self) -> EventType {
		return match self {
			ApplicationEvent::Resize{ width: _, height: _ } => EventType::AppResize,
            ApplicationEvent::Update => EventType::AppUpdate,
            ApplicationEvent::Render => EventType::AppRender,
			ApplicationEvent::Close => EventType::AppClose,
			ApplicationEvent::Tick => EventType::AppTick,
		};
	}
	fn GetCategoryFlags(self: &Self) -> u64 {
		return EventCategory::Application.ToU64();
	}
}

#[derive(Debug)]
pub enum KeyEvent {
	KeyPressed{ keyCode: u64, repeatCount: u64 },
	KeyReleased{ keyCode: u64 },
	CharacterTyped{ charCode: u64 },
}
impl Event for KeyEvent {
	fn GetName(self: &Self) -> &str {
		return match self {
			KeyEvent::KeyPressed{ keyCode: _, repeatCount: _ } => "KeyPressed",
			KeyEvent::KeyReleased{ keyCode: _ } => "KeyReleased",
			KeyEvent::CharacterTyped{ charCode: _ } => "CharacterTyped",
		};
	}
	fn GetEventType(self: &Self) -> EventType {
		return match self {
			KeyEvent::KeyPressed{ keyCode: _, repeatCount: _ } => EventType::KeyPressed,
			KeyEvent::KeyReleased{ keyCode: _ } => EventType::KeyReleased,
			KeyEvent::CharacterTyped{ charCode: _ } => EventType::CharacterTyped,
		};
	}
	fn GetCategoryFlags(self: &Self) -> u64 {
        return EventCategory::Input | EventCategory::Keyboard;
    }
}

#[derive(Debug)]
pub enum MouseEvent {
	MouseMoved{ x: u64, y: u64 },
	MouseScrolled{ x: u64, y: u64 },
	MousePressed{ mouseButton: u64 },
	MouseReleased{ mouseButton: u64 },
}
impl Event for MouseEvent {
	fn GetName(self: &Self) -> &str {
		return match self {
			MouseEvent::MouseMoved{ x: _, y: _ } => "MouseMoved",
			MouseEvent::MouseScrolled{ x: _, y: _ } => "MouseScrolled",
			MouseEvent::MousePressed{ mouseButton: _ } => "MouseClicked",
			MouseEvent::MouseReleased{ mouseButton: _ } => "MouseReleased",
		};
	}
	fn GetEventType(self: &Self) -> EventType {
		return match self {
			MouseEvent::MouseMoved{ x: _, y: _ } => EventType::MouseMoved,
			MouseEvent::MouseScrolled{ x: _, y: _ } => EventType::MouseScrolled,
			MouseEvent::MousePressed{ mouseButton: _ } => EventType::MousePressed,
			MouseEvent::MouseReleased{ mouseButton: _ } => EventType::MouseReleased,
		};
	}
	fn GetCategoryFlags(self: &Self) -> u64 {
		return match self {
			MouseEvent::MousePressed{ mouseButton: _ } => EventCategory::Input | EventCategory::Mouse | EventCategory::MouseButton,
			MouseEvent::MouseReleased{ mouseButton: _ } => EventCategory::Input | EventCategory::Mouse | EventCategory::MouseButton,
			_ => EventCategory::Input | EventCategory::Mouse,
		};
	}
}
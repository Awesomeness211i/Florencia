pub mod keyevent;
pub mod mouseevent;
pub mod applicationevent;

pub trait Event: std::fmt::Debug {
	fn GetName(self: &Self) -> &str;
	fn GetCategoryFlags(self: &Self) -> u64;
	fn GetEventType(self: &Self) -> EventType;
	fn ToString(self: &Self) -> String { String::from(self.GetName()) }
	fn IsInCategory(self: &Self, category: EventCategory) -> u64 { self.GetCategoryFlags() & category }
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
	None = 0b0,
	Application = 0b1,
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
impl std::ops::BitAnd for EventCategory {
	type Output = u64;
	fn bitand(self, rhs: EventCategory) -> Self::Output {
		return self.ToU64() & rhs;
	}
}
impl std::ops::BitOr<EventCategory> for u64 {
	type Output = u64;
	fn bitor(self: Self, rhs: EventCategory) -> Self::Output {
		return self | rhs.ToU64();
	}
}
impl std::ops::BitAnd<EventCategory> for u64 {
	type Output = u64;
	fn bitand(self, rhs: EventCategory) -> Self::Output {
		return self & rhs.ToU64();
	}
}
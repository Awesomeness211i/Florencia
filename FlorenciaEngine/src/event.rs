pub mod keyevent;
pub mod mouseevent;
pub mod applicationevent;

pub trait Event: std::fmt::Debug {
	fn GetName(&self) -> &str;
	fn GetCategoryFlags(&self) -> u64;
	fn GetEventType(&self) -> EventType;
	fn ToString(&self) -> String { String::from(self.GetName()) }
	fn IsInCategory(&self, category: EventCategory) -> u64 { self.GetCategoryFlags() & category }
}
impl std::fmt::Display for dyn Event {
	fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
		write!(f, "{:#?}", self)
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
		write!(f, "{:#?}", self)
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
	pub fn ToU64(self) -> u64 {
		self as u64
	}
}
impl std::ops::BitOr for EventCategory {
	type Output = u64;
	fn bitor(self, rhs: EventCategory) -> Self::Output {
		self.ToU64() | rhs.ToU64()
	}
}
impl std::ops::BitAnd for EventCategory {
	type Output = u64;
	fn bitand(self, rhs: EventCategory) -> Self::Output {
		self.ToU64() & rhs
	}
}
impl std::ops::BitOr<EventCategory> for u64 {
	type Output = u64;
	fn bitor(self, rhs: EventCategory) -> Self::Output {
		self | rhs.ToU64()
	}
}
impl std::ops::BitAnd<EventCategory> for u64 {
	type Output = u64;
	fn bitand(self, rhs: EventCategory) -> Self::Output {
		self & rhs.ToU64()
	}
}

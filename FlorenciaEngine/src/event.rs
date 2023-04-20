pub enum EventType {
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,
	KeyPressed, KeyReleased, CharacterTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
}

pub enum EventCategory {
	None = 0,
	Application = 1,
	Input = 0b10,
	Keyboard = 0b100,
	Mouse = 0b1000,
	MouseButton = 0b10000,
}

pub trait Event {
	fn GetName(self: &Self) -> &str;
	fn GetCategoryFlags(self: &Self) -> usize;
	fn GetEventType(self: &Self) -> EventType;
	fn ToString(self: &Self) -> String { String::from(self.GetName()) }
	//fn IsInCategory(self: &Self, category: EventCategory) -> bool { self.GetCategoryFlags() & cateory }
}
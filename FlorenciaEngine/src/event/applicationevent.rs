use super::*;

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
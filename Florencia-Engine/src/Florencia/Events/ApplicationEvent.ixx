export module ApplicationEvent;
export import Event;
import <sstream>;

export namespace Florencia {

	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(uint32_t width, uint32_t height) : m_Width(width), m_Height(height) {}

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		int GetCategoryFlags() const override { return (int)EventCategory::EventCategoryApplication; }

		const char* GetName() const override { return "WindowResize"; }
		static EventType GetStaticType() { return EventType::WindowResize; }
		EventType GetEventType() const override { return GetStaticType(); }
	private:
		uint32_t m_Width, m_Height;
	};

	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() = default;

		int GetCategoryFlags() const override { return (int)EventCategory::EventCategoryApplication; }

		const char* GetName() const override { return "WindowClose"; }
		static EventType GetStaticType() { return EventType::WindowClose; }
		EventType GetEventType() const override { return GetStaticType(); }
	};

	class AppTickEvent : public Event {
	public:
		AppTickEvent() = default;

		int GetCategoryFlags() const override { return (int)EventCategory::EventCategoryApplication; }

		const char* GetName() const override { return "AppTick"; }
		static EventType GetStaticType() { return EventType::AppTick; }
		EventType GetEventType() const override { return GetStaticType(); }
	};

	class AppUpdateEvent : public Event {
	public:
		AppUpdateEvent() = default;

		int GetCategoryFlags() const override { return (int)EventCategory::EventCategoryApplication; }

		const char* GetName() const override { return "AppUpdate"; }
		static EventType GetStaticType() { return EventType::AppUpdate; }
		EventType GetEventType() const override { return GetStaticType(); }
	};

	class AppRenderEvent : public Event {
	public:
		AppRenderEvent() = default;

		int GetCategoryFlags() const override { return (int)EventCategory::EventCategoryApplication; }

		const char* GetName() const override { return "AppRender"; }
		static EventType GetStaticType() { return EventType::AppRender; }
		EventType GetEventType() const override { return GetStaticType(); }
	};

}
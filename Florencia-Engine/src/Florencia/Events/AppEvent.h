#pragma once
#include "Event.h"

namespace Florencia {

	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		//EVENT_CLASS_TYPE(WindowResize)
		static EventType GetStaticType() { return EventType::WindowResize; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "WindowResize"; }
		//EVENT_CLASS_CATEGORY(EventCategoryApplication)
		int GetCategoryFlags() const override { return (int)EventCategory::Application; }
	private:
		unsigned int m_Width, m_Height;
	};

	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() = default;

		//EVENT_CLASS_TYPE(WindowClose)
		static EventType GetStaticType() { return EventType::WindowClose; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "WindowClose"; }
		//EVENT_CLASS_CATEGORY(EventCategoryApplication)
		int GetCategoryFlags() const override { return (int)EventCategory::Application; }
	};

	class AppTickEvent : public Event {
	public:
		AppTickEvent() = default;

		//EVENT_CLASS_TYPE(AppTick)
		static EventType GetStaticType() { return EventType::AppTick; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "AppTick"; }
		//EVENT_CLASS_CATEGORY(EventCategoryApplication)
		int GetCategoryFlags() const override { return (int)EventCategory::Application; }
	};

	class AppUpdateEvent : public Event {
	public:
		AppUpdateEvent() = default;

		//EVENT_CLASS_TYPE(AppUpdate)
		static EventType GetStaticType() { return EventType::AppUpdate; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "AppUpdate"; }
		//EVENT_CLASS_CATEGORY(EventCategoryApplication)
		int GetCategoryFlags() const override { return (int)EventCategory::Application; }
	};

	class AppRenderEvent : public Event {
	public:
		AppRenderEvent() = default;

		//EVENT_CLASS_TYPE(AppRender)
		static EventType GetStaticType() { return EventType::AppRender; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "AppRender"; }
		//EVENT_CLASS_CATEGORY(EventCategoryApplication)
		int GetCategoryFlags() const override { return (int)EventCategory::Application; }
	};

}
#pragma once
#include <sstream>

#define LEFT(x) (1 << x)

namespace Florencia {

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum class EventCategory {
		None,
		Application = LEFT(0),
		Input		= LEFT(1),
		Keyboard	= LEFT(2),
		Mouse		= LEFT(3),
		MouseButton = LEFT(4)
	};

	class Event {
	public:
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category) { return GetCategoryFlags() & (int)category; }

		bool Handled = false;
	};

	class EventDispatcher {
	public:
		EventDispatcher(Event& event) : m_Event(event) {}

		template<typename T, typename F>
		bool Dispatch(const F& func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.ToString(); }
}
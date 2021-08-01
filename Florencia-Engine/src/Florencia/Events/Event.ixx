module;
#include <iostream>
export module Event;

export namespace Florencia {

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, CharacterTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum class EventCategory {
		None = 0B00000,
		EventCategoryApplication = 0B00001,
		EventCategoryInput = 0B00010,
		EventCategoryKeyboard = 0B00100,
		EventCategoryMouse = 0B01000,
		EventCategoryMouseButton = 0B10000
	};

	class Event {
	public:
		virtual ~Event() = default;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual EventType GetEventType() const = 0;
		virtual std::string ToString() const { return GetName(); }
		bool IsInCategory(EventCategory category) { return (int)GetCategoryFlags() & (int)category; }

		bool Handled = false;
	};

	class EventDispatcher {
	public:
		EventDispatcher() {}

		//func will be deduced by the compiler and assumes a return of bool type
		template<typename Event_t>
		bool Dispatch(Event& e, auto func) {
			//Assumes that all events have a static function called GetStaticType()
			if (e.GetEventType() == Event_t::GetStaticType()) {
				return e.Handled = e.Handled || func(static_cast<Event_t&>(e));
			}
			return false;
		}

	} EventHandler;

	inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.ToString(); }
}
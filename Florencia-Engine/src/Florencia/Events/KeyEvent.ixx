export module KeyEvent;
export import Event;
import KeyCodes;

import <stdint.h>;
import <sstream>;

export namespace Florencia {

	class KeyEvent : public Event {
	public:
		Key GetKeyCode() const { return m_KeyCode; }
		int GetCategoryFlags() const override { return (int)EventCategory::EventCategoryInput | (int)EventCategory::EventCategoryKeyboard; }

	protected:
		KeyEvent(const Key keycode) { m_KeyCode = keycode; }
		Key m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(const Key keycode, const uint16_t repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		uint16_t GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << (int)m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		const char* GetName() const override { return "KeyPressed"; }
		static EventType GetStaticType() { return EventType::KeyPressed; }
		EventType GetEventType() const override { return GetStaticType(); }
	private:
		uint16_t m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(const Key keycode) : KeyEvent(keycode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << (int)m_KeyCode;
			return ss.str();
		}

		const char* GetName() const override { return "KeyReleased"; }
		static EventType GetStaticType() { return EventType::KeyReleased; }
		EventType GetEventType() const override { return GetStaticType(); }
	};

	class CharacterTypedEvent : public Event {
	public:
		CharacterTypedEvent(const Character charactercode) : m_CharacterCode(charactercode) {}

		Character GetCharacterCode() const { return m_CharacterCode; }
		int GetCategoryFlags() const override { return (int)EventCategory::EventCategoryInput | (int)EventCategory::EventCategoryKeyboard; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "CharacterTypedEvent: " << (char)m_CharacterCode;
			return ss.str();
		}

		const char* GetName() const override { return "CharacterTyped"; }
		static EventType GetStaticType() { return EventType::CharacterTyped; }
		EventType GetEventType() const override { return GetStaticType(); }
	private:
		Character m_CharacterCode;
	};

}
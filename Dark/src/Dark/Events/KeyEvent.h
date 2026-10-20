#pragma once

#include "Event.h"

#include "Dark/Core/KeyCodes.h"

namespace Dark {

	class DARK_API KeyEvent : public Event {

	protected:
		KeyCode m_KeyCode{};

		KeyEvent(KeyCode keycode)
			: m_KeyCode(keycode) {

		}

	public:
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

		inline KeyCode GetKeyCode() const { return m_KeyCode; }

	};

	class DARK_API KeyPressedEvent : public KeyEvent {

		int m_RepeatCount{};

	public:
		KeyPressedEvent(KeyCode KeyCode, int repeatCount)
			: KeyEvent(KeyCode), m_RepeatCount(repeatCount) { }

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			 
			ss << "KeyPressedEvent: " << (int)m_KeyCode << "(Repeats: " << m_RepeatCount << ")";

			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);

	};

	class DARK_API KeyReleasedEvent : public KeyEvent {

	public:
		KeyReleasedEvent(KeyCode KeyCode)
			: KeyEvent(KeyCode) { }

		std::string ToString() const override{
			std::stringstream ss;

			ss << "KeyReleasedEvent: " << (int)m_KeyCode;

			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);

	};

	class DARK_API KeyTypedEvent : public KeyEvent {

	public:
		KeyTypedEvent(KeyCode keycode)
			: KeyEvent(keycode) { }

		std::string ToString() const override {
			std::stringstream ss;

			ss << "KeyPressedEvent: " << (int)m_KeyCode;

			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped);

	};

}
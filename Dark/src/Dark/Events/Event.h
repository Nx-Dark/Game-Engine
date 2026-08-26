#pragma once

#include "Dark/Core/Core.h"

namespace Dark {

	// Currently Blocking Event system.
	// When a Event Occurs, the program stops, deals with the event in that exact moment and continue
	// TODO: Make it Buffered Event System Later!


	enum class EventType {

		None = 0,
		
		WindowResize, WindowClose, WindowMoved, WindowFocus, WindowLostFocus, //Window Event Types
		AppTick, AppRender, AppUpdate, //Application Event types
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled, //Mouse Event Types
		KeyPressed, KeyReleased, KeyTyped //KeyBoard key Event Types

	};

	enum EventCategory {
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

//macros to make life easier
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
							   virtual EventType GetEventType() const override { return GetStaticType(); }\
							   virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	//Event class decl
	class DARK_API Event {

		friend class EventDispatcher;

	protected:
		bool m_Handled{};

	public:

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;

		virtual std::string ToString() const { return static_cast<std::string>(GetName()); }

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}

		inline bool Handled() const{ return m_Handled; }

	};
	
	//Event dispatcher, for the engine only!
	class EventDispatcher {

		//template <typename T>
		//using EventFn = std::function<bool(T&)>;

		Event& m_Event;

	public:
		EventDispatcher(Event& e) : m_Event(e) { }

		template <typename T, typename F>
		bool Dispatch(const F& func) {

			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_Handled = func(static_cast<T&>(m_Event));
				return true;
			}

			return false;
		}
	};

	//For logging Events
	inline std::string format_as(const Event& e) {
		return e.ToString();
	}

}
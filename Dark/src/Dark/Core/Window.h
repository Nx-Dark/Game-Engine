#pragma once

#include "Dark/Core/Core.h"
#include "Dark/Events/Event.h"

namespace Dark {

	//window properties struct
	struct WindowProps {
		std::string title;
		uint32_t width;
		uint32_t height;

		WindowProps(
			const std::string& t = "Dark Engine",
			uint32_t w = 960,
			uint32_t h = 540
		)
			: title(t), width(w), height(h) { }
	};

	//Window Interface for Desktop windows(Abstract window class, cannot be instantiated)
	class DARK_API Window {

	public:

		using EventCallBackFn = std::function<void(Event&)>;

		virtual ~Window() {}
		
		virtual void OnUpdate() = 0;

		//window properties
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual const std::string& GetTitle() const = 0;

		//vsync
		virtual void SetVsync(bool val) = 0;
		virtual bool IsVsync() const = 0;

		//event call back function
		virtual void SetEventCallBackFn(const EventCallBackFn& callBackFn) = 0;

		//get void pointer to the native window(pure virtual function, must be implemented in the derived class)
		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());

	};

}
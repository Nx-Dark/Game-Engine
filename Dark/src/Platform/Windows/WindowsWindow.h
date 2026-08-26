#pragma once

#include "Dark/Core/Window.h"
#include "Dark/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Dark {

	class WindowsWindow : public Window
	{
	private:
		struct WindowData {
			std::string title;
			uint32_t width, height;
			bool isVsync;

			EventCallBackFn CallBackFn;
		};

		GLFWwindow* m_Window;
		WindowData m_Data;

		GraphicsContext* m_Context{ nullptr };

	public:
		WindowsWindow(const WindowProps& props);

		virtual ~WindowsWindow();

		virtual void OnUpdate() override;

		//win props
		virtual inline uint32_t GetWidth() const override { return m_Data.width; }
		virtual inline uint32_t GetHeight() const override { return m_Data.height; }
		virtual inline const std::string& GetTitle() const override { return m_Data.title; }

		//vsync
		virtual void SetVsync(bool val) override;
		virtual bool IsVsync() const override;

		//event call back
		virtual inline void SetEventCallBackFn(const EventCallBackFn& callBackFn) override { m_Data.CallBackFn = callBackFn; }

		//return void pointer to the native window
		inline virtual void* GetNativeWindow() const override { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();
	};

}


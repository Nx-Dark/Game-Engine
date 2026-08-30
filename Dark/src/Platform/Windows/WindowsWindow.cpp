#include "dpch.h"
#include "WindowsWindow.h"

#include "Dark/Events/ApplicationEvent.h"
#include "Dark/Events/Event.h"
#include "Dark/Events/KeyEvent.h"
#include "Dark/Events/MouseEvent.h"

#include "GLFW/glfw3.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Dark {

	static bool s_GLFWinit{ false };

	static void GLFWerrorCallBack(int error_code, const char* description) {
		DARK_CORE_ERROR("GLFW ERROR ({0}) : {1}", error_code, description);
	}

	Scope<Window> Window::Create(const WindowProps& props) {
		return CreateScope<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		DARK_PROFILE_FUNCTION();

		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		DARK_PROFILE_FUNCTION();

		ShutDown();
	}

	void WindowsWindow::Init(const WindowProps& props) {

		DARK_PROFILE_FUNCTION();

		m_Data.title = props.title;
		m_Data.width = props.width;
		m_Data.height = props.height;
		
		DARK_CORE_INFO("Creating Window {0}, {1}, {2}", m_Data.title, m_Data.width, m_Data.height);

		if (!s_GLFWinit) 
		{
			DARK_PROFILE_SCOPE("glfwInit");

			bool success = glfwInit();
			DARK_CORE_ASSERT(success, "Could Not Initialize GLFW!");

			glfwSetErrorCallback(GLFWerrorCallBack);

			s_GLFWinit = success;
		}

		{
			DARK_PROFILE_SCOPE("glfwCreateWindow");
			m_Window = glfwCreateWindow(
				static_cast<int>(m_Data.width), static_cast<int>(m_Data.height),
				m_Data.title.c_str(), nullptr, nullptr
			);
		}

		//creating a new opengl context
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();
		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVsync(true);

		//set GLFW event callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {

			WindowData& data{ *(WindowData*)(glfwGetWindowUserPointer(window)) };

			data.width = width;
			data.height = height;
			
			WindowResizeEvent event(width, height);
			data.CallBackFn(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			
			WindowData& data{ *(WindowData*)(glfwGetWindowUserPointer(window)) };
			WindowCloseEvent event;
			data.CallBackFn(event);

		});
		
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			
			WindowData& data{ *(WindowData*)(glfwGetWindowUserPointer(window)) };

			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent event(key, 0);
					data.CallBackFn(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent event(key);
					data.CallBackFn(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(key, 1);
					data.CallBackFn(event);
					break;
				}
			}

		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int character) {

			WindowData& data{ *(WindowData*)(glfwGetWindowUserPointer(window)) };

			KeyTypedEvent event(character);
			data.CallBackFn(event);

		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mod) {
			
			WindowData& data{ *(WindowData*)(glfwGetWindowUserPointer(window)) };

			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.CallBackFn(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.CallBackFn(event);
					break;
				}
			}

		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			
			WindowData& data{ *(WindowData*)(glfwGetWindowUserPointer(window)) };

			MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
			data.CallBackFn(event);

		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {

			WindowData& data{ *(WindowData*)(glfwGetWindowUserPointer(window)) };

			MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
			data.CallBackFn(event);

		});
	}

	void WindowsWindow::ShutDown() {
		//TODO: glfwTerminate() on shutdown
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	//vsync
	void WindowsWindow::SetVsync(bool val) {
		DARK_PROFILE_FUNCTION();

		glfwSwapInterval(val);

		m_Data.isVsync = val;
	}

	bool WindowsWindow::IsVsync() const{
		return m_Data.isVsync; 
	}
}
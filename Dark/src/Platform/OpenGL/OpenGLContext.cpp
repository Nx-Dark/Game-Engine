#include "dpch.h"

#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Dark {

	OpenGLContext::OpenGLContext(GLFWwindow* winHandle)
		: m_WinHandle(winHandle) { 

		DARK_CORE_ASSERT(m_WinHandle, "Window Handle is Null!");

	}


	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WinHandle);
		int glad_load_status{ gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) };
		DARK_CORE_ASSERT(glad_load_status, "Failed to Load GLAD!");
		
		////opengl info
		DARK_CORE_INFO("OpenGL Info:");
		DARK_CORE_INFO("	Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		DARK_CORE_INFO("	Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		DARK_CORE_INFO("	Version: {0}", (const char*)glGetString(GL_VERSION));

#ifdef DARK_ENABLE_ASSERTS
		int versionMajor{};
		int versionMinor{};
		
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		DARK_CORE_ASSERT((versionMajor == 4 && versionMinor >= 5), "Dark Engine Requries OpenGL Core Version 4.5 or Above!");

#endif

	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WinHandle);
	}

}
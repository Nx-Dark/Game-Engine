#pragma once

#include "Dark/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Dark {

	class OpenGLContext : public GraphicsContext {

	private:
		GLFWwindow* m_WinHandle{ nullptr };

	public:

		OpenGLContext(GLFWwindow* winHandle);

		virtual ~OpenGLContext();

		virtual void Init() override;
		virtual void SwapBuffers() override;

	};

}
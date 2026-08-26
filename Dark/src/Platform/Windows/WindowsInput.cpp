#include "dpch.h"
#include "WindowsInput.h"

#include "Dark/Core/Application.h"

#include "GLFW/glfw3.h"

namespace Dark {

	Input* Input::s_Instance{ new WindowsInput() };

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window{ static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()) };
		auto state{ glfwGetKey(window, keycode) };
		return state == DK_PRESS || state == DK_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window{ static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()) };
		auto state{ glfwGetMouseButton(window, button) };
		return state == DK_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl() {
		auto window{ static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()) };
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { static_cast<float>(xPos), static_cast<float>(yPos) };
	}

	float WindowsInput::GetMouseXImpl() {
		auto [x, y] {GetMousePos()};
		return x;
	}

	float WindowsInput::GetMouseYImpl() {
		auto [x, y] {GetMousePos()};
		return y;
	}
}
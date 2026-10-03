#include "dpch.h"

#include "Dark/Core/Input.h"

#include "Dark/Core/Application.h"

#include "GLFW/glfw3.h"

namespace Dark {

	bool Input::IsKeyPressed(int keycode)
	{
		auto window{ static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()) };
		auto state{ glfwGetKey(window, keycode) };
		return state == DK_PRESS || state == DK_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		auto window{ static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()) };
		auto state{ glfwGetMouseButton(window, button) };
		return state == DK_PRESS;
	}

	std::pair<float, float> Input::GetMousePos() {
		auto window{ static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()) };
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { static_cast<float>(xPos), static_cast<float>(yPos) };
	}

	float Input::GetMouseX() {
		auto [x, y] {GetMousePos()};
		return x;
	}

	float Input::GetMouseY() {
		auto [x, y] {GetMousePos()};
		return y;
	}
}
#include "dpch.h"

#ifdef DARK_PLATFORM_WINDOWS

#include "Dark/Core/Input.h"

#include "Dark/Core/Application.h"

#include "GLFW/glfw3.h"

namespace Dark {

	bool Input::IsKeyPressed(KeyCode keycode)
	{
		GLFWwindow* window{ static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()) };
		auto state{ glfwGetKey(window, (int)keycode) };
		return state == (int)DK_PRESS || state == (int)DK_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		GLFWwindow* window{ static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()) };
		auto state{ glfwGetMouseButton(window, (int)button) };
		return state == (int)DK_PRESS;
	}

	bool Input::IsGamePadButtonPressed(GamePadCode padcode)
	{
		return false;
	}

	bool Input::IsJoyStickButtonPressed(JoyStickCode joycode)
	{
		return false;
	}

	std::pair<float, float> Input::GetMousePos() {
		GLFWwindow* window{ static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()) };
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

	//mouse pointer stuff
	void Input::ShowMousePointer()
	{
		GLFWwindow* window{ static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()) };
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void Input::HideMousePointer()
	{
		GLFWwindow* window{ static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()) };
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}

	void Input::DisableMousePointer()
	{
		GLFWwindow* window{ static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()) };
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

#endif
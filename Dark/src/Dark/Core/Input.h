#pragma once

#include "Dark/Core/Core.h"

#include "Dark/Core/KeyCodes.h"
#include "Dark/Core/GamePadCodes.h"
#include "Dark/Core/JoyStickCodes.h"
#include "Dark/Core/MouseButtonCodes.h"

namespace Dark {

	class DARK_API Input
	{

	public:

		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePos();
		static float GetMouseX();
		static float GetMouseY();

	};

}
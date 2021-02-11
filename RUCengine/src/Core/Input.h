#pragma once

#include "KeyCodes.h"

#include <utility>

namespace RUC
{
	class Input
	{
	public:
		static bool IsKeyPressed(int keycode);

		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMousePosX() { return GetMousePosition().first; }
		static float GetMousePosY() { return GetMousePosition().second; }
	};
}
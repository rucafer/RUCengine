#pragma once

#include <chrono>

namespace RUC
{
	class Timestep
	{
	public:
		static void Update();

		static float Get() { return s_Time; }
		static float GetSeconds() { return s_Time; }
		static float GetMilliseconds() { return s_Time * 1000.0f; }

	private:
		static std::chrono::steady_clock::time_point s_LastFrame;
		static float s_Time;
	};
}
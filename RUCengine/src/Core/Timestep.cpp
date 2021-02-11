#include "Timestep.h"

namespace RUC
{
	std::chrono::steady_clock::time_point Timestep::s_LastFrame;
	float Timestep::s_Time;

	void Timestep::Update()
	{
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

		std::chrono::duration<float> duration = now - s_LastFrame;

		s_Time = duration.count();

		s_LastFrame = now;
	}
}
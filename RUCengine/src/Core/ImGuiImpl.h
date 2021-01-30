#pragma once

namespace RUC
{
	class ImGuiImpl
	{
	public:
		static void Init();
		static void ShutDown();

		static void BeginFrame();
		static void EndFrame();
	};
}
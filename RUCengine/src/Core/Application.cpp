#include "Base.h"
#include "Application.h"
#include "Log/Log.h"

#include <iostream>

namespace RUC
{
	Application::Application(const char* name)
		: m_AppName(name)
	{
		Log::Init();

		Log::GetCoreLogger()->trace("Core test");
		Log::GetClientLogger()->trace("App test");

		Log::GetCoreLogger()->warn("Core test warning");
		Log::GetClientLogger()->warn("App test warning");

		Log::GetCoreLogger()->error("Core test error");
		Log::GetClientLogger()->error("App test error");
	}

	void Application::Run()
	{
		while (true)
		{
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}
		}
	}
}
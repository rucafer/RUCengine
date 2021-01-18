#include "Base.h"
#include "Application.h"

#include <iostream>
#include "Log/Log.h"

namespace RUC
{
	Application::Application(const char* name)
		: m_AppName(name)
	{
		Log::Init();

		RUC_INFO("App info test {}", 42);
		RUC_TRACE("App trace test {}", 42);
		RUC_WARN("App warning test {}", 42);
		RUC_ERROR("App error test {}", 42);
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
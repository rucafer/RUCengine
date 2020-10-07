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
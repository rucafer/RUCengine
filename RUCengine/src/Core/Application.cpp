#include "Base.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/EventDispatcher.h"

#include <iostream>

namespace RUC
{
	static bool EventTest1(WindowResizedEvent& e)
	{
		RUC_INFO("WindowResizedEvent: {}-{}", e.GetWidth(), e.GetHeight());
		return false;
	}
	static bool EventTest2(KeyDownEvent& e)
	{
		RUC_INFO("KeyDownEvent: {}", e.GetKeyCode());
		return false;
	}

	Application::Application(const char* name)
		: m_AppName(name)
	{
		Log::Init();

		//Logger Test
		RUC_INFO("App info test {}", 42);
		RUC_TRACE("App trace test {}", 42);
		RUC_WARN("App warning test {}", 42);
		RUC_ERROR("App error test {}", 42);

		//Events test
		WindowResizedEvent wce(100.0, 200.0);
		KeyDownEvent kde(5);

		EventDispatcher disp1(wce);
		EventDispatcher disp2(kde);

		disp1.Dispatch<WindowResizedEvent>(EventTest1);
		disp1.Dispatch<KeyDownEvent>(EventTest2);

		disp2.Dispatch<WindowResizedEvent>(EventTest1);
		disp2.Dispatch<KeyDownEvent>(EventTest2);

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
#include "Base.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/EventDispatcher.h"

#include <GLFW/glfw3.h>

#include <iostream>

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace RUC
{
	Application::Application(const char* name)
		: m_AppName(name)
	{
		Log::Init();
		RUC_ASSERT(glfwInit(), "Failed to initialize GLFW");
		m_Window = std::unique_ptr<Window>(Window::Create(WindowProps("Test window")));

		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			for (Layer* layer : *m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_Window->OnUpdate();

		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(Application::OnWindowClose));
	}

	bool Application::OnWindowClose(WindowClosedEvent& e)
	{
		m_Running = false;
		return true;
	}
}
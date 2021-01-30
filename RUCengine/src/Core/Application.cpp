#include "Base.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/EventDispatcher.h"

#include "ImGuiImpl.h"

#include "Input.h"

#include <GLFW/glfw3.h>

#include <iostream>

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace RUC
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const char* name)
		: m_AppName(name)
	{
		RUC_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		Log::Init();
		RUC_ASSERT(glfwInit(), "Failed to initialize GLFW");
		m_Window = std::unique_ptr<Window>(Window::Create(WindowProps("Test window")));

		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		ImGuiImpl::Init();
	}

	Application::~Application()
	{
		ImGuiImpl::ShutDown();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			for (Layer* layer : *m_LayerStack)
			{
				layer->OnUpdate();
			}

			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);


			ImGuiImpl::BeginFrame();
			for (Layer* layer : *m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			ImGuiImpl::EndFrame();

			if (Input::IsKeyPressed(32))
			{
				RUC_INFO("Space key pressed");
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
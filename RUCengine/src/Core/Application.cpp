#include "Base.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/EventDispatcher.h"

#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer.h"

#include "ImGuiImpl.h"

#include "Input.h"

#include "Timestep.h"

#include <GLFW/glfw3.h>

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

		Renderer::Init();

		ImGuiImpl::Init();

		//Update the timestep so that it has a correct initial value
		Timestep::Update();
	}

	Application::~Application()
	{
		ImGuiImpl::ShutDown();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			Timestep::Update();

			//Update layers
			for (Layer* layer : *m_LayerStack)
			{
				layer->OnUpdate();
			}

			//Render
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RenderCommand::Clear();

			for (Layer* layer : *m_LayerStack)
			{
				layer->OnRender();
			}

			//ImGui render
			ImGuiImpl::BeginFrame();
			for (Layer* layer : *m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			ImGuiImpl::EndFrame();
			

			//Update window
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FN(Application::OnWindowResize));
	}

	bool Application::OnWindowClose(WindowClosedEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizedEvent& e)
	{
		//TODO: handle minimized window

		Renderer::SetViewportSize(e.GetWidth(), e.GetHeight());
		FrameBuffer::ResizeAllResizables(e.GetWidth(), e.GetHeight());

		return false;	//Other parts of the code may need to be notified by the resize
	}
}
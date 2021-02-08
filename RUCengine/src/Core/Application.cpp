#include "Base.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/EventDispatcher.h"

#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer.h"

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

		Renderer::Init();

		ImGuiImpl::Init();


		m_Shader.reset(Shader::Create("assets/shaders/DefaultShader.glsl"));
	}

	Application::~Application()
	{
		ImGuiImpl::ShutDown();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			//Update layers
			for (Layer* layer : *m_LayerStack)
			{
				layer->OnUpdate();
			}

			//Render
			RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
			RenderCommand::Clear();

			m_Shader->Bind();
			m_Shader->UploadUniformMat4("u_Transform", glm::mat4(0.5f));

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
	}

	bool Application::OnWindowClose(WindowClosedEvent& e)
	{
		m_Running = false;
		return true;
	}
}
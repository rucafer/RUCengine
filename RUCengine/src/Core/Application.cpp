#include "Application.h"
#include "Log/Log.h"

#include <iostream>

namespace RUC
{
	Application::Application(const char* name)
		: m_AppName(name)
	{
		Log::Init();

		m_LayerStack.Push(new Layer("2"));
		m_LayerStack.Push(new Layer("3"));
		m_LayerStack.Push(new Layer("4"));
		m_LayerStack.PushOnTop(new Layer("1"));
		m_LayerStack.PushOnTop(new Layer("0"));
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
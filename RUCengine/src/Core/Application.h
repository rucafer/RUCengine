#pragma once

#include "Base.h"
#include "Layers/LayerStack.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

#include <string>

namespace RUC {

	class Application {
	public:
		Application(const char* name);

		~Application();

		void Run();

		void OnEvent(Event& event);

		void SetLayers(LayerStack* layerStack) { m_LayerStack = layerStack; }

	private:
		bool OnWindowClose(WindowClosedEvent& e);

	private:
		const char* m_AppName;

		LayerStack* m_LayerStack;

		std::unique_ptr<Window> m_Window;

		bool m_Running = true;
	};

	extern const char* GetAppName();

	extern void RegisterLayers(LayerStack* layerStack);
}
#pragma once

#include "Base.h"
#include "Layers/LayerStack.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

#include "Renderer/Shader.h"

#include <string>

namespace RUC {

	class Application {
	public:
		Application(const char* name);

		~Application();

		void Run();

		void OnEvent(Event& event);

		void SetLayers(LayerStack* layerStack) { m_LayerStack = layerStack; }

		Window& GetWindow() { return *m_Window; }

		static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowClosedEvent& e);
		bool OnWindowResize(WindowResizedEvent& e);

	private:
		const char* m_AppName;

		LayerStack* m_LayerStack;

		std::unique_ptr<Window> m_Window;

		bool m_Running = true;

	private:
		static Application* s_Instance;
	};

	extern const char* GetAppName();

	extern void RegisterLayers(LayerStack* layerStack);
}
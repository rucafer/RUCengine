#pragma once

#include "Base.h"
#include "Layers/LayerStack.h"

#include <string>

namespace RUC {

	class Application {
	public:
		Application(const char* name);

		virtual ~Application() = default;

		void Run();

		void SetLayers(LayerStack* layerStack) { m_LayerStack = *layerStack; }

	private:
		const char* m_AppName;

		LayerStack m_LayerStack;
	};

	extern const char* GetAppName();

	extern void RegisterLayers(LayerStack* layerStack);
}
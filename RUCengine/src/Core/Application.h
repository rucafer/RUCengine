#pragma once

#include "Base.h"
#include "Layers/LayerStack.h"

#include <string>

namespace RUC {

	class RUCAPI Application {
	public:
		Application(const char* name);

		virtual ~Application() = default;

		void Run();

	private:
		const char* m_AppName;

		LayerStack m_LayerStack;
	};

	extern const char* GetAppName();
}
#include <Core/EntryPoint.h>
#include <Core/Application.h>
#include <Log/Log.h>

#include <stdio.h>

namespace RUC {

	class Sandbox : public Application {
	public:
		Sandbox()
		{
			
		}

		~Sandbox() = default;
	};

	Application* CreateApp() {
		return new Sandbox();
	}
}
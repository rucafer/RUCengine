#pragma once

namespace RUC {

	class Application {
	public:
		Application() = default;

		virtual ~Application() = default;

		void Run();

	private:

	};

	Application* CreateApp();
}
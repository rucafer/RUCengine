#pragma once

#include "Core/Window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace RUC
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& properties);
		~WindowsWindow();

		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;

		void OnUpdate() override;

		void SetEventCallback(EventCallback eventCallback) override;

	private:

		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			EventCallback Callback;
		};
		WindowData m_Data;
	};
}
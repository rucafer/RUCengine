#pragma once

#include "Events/Event.h"

#include <string>
#include <functional>

namespace RUC
{
	struct WindowProps
	{
		std::string Title;
		int Width, Height;

		WindowProps(const std::string& title = "Untitled window", int width = 1280, int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class Window
	{
	public:
		virtual ~Window() = default;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void OnUpdate() = 0;

		using EventCallback = std::function<void(Event&)>;

		virtual void  SetEventCallback(EventCallback callback) = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& properties);

	protected:
		static int s_WindowCount;
	};
}
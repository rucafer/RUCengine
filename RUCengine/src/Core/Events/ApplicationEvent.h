#pragma once

#include"Event.h"

namespace RUC
{
	class WindowClosedEvent : public Event
	{
	public:
		SET_EVENT_TYPE(WindowClosedEvent)
	};

	class WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(int width, int height) : m_Width(width), m_Height(height) {}

		SET_EVENT_TYPE(WindowResizedEvent)

		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }
	private:
		int m_Width, m_Height;
	};
}
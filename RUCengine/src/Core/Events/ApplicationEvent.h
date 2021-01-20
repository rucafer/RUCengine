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
		WindowResizedEvent(float width, float height) : m_Width(width), m_Height(height) {}

		SET_EVENT_TYPE(WindowResizedEvent)

		float GetWidth() { return m_Width; }
		float GetHeight() { return m_Height; }
	private:
		float m_Width, m_Height;
	};
}
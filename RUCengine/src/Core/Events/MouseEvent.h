#pragma once

#include "Event.h"

namespace RUC
{
	class MouseButtonDownEvent: public Event
	{
	public:
		MouseButtonDownEvent(int buttonCode) : m_ButtonCode(buttonCode) {}

		int GetButtonCode() const { return m_ButtonCode; }

		SET_EVENT_TYPE(MouseButtonDownEvent)
	private:
		int m_ButtonCode;
	};

	class MouseButtonUpEvent : public Event
	{
	public:
		MouseButtonUpEvent(int buttonCode) : m_ButtonCode(buttonCode) {}

		int GetButtonCode() const { return m_ButtonCode; }

		SET_EVENT_TYPE(MouseButtonUpEvent)
	private:
		int m_ButtonCode;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(double xOffset, double yOffset) : m_xOffset(xOffset), m_yOffset(yOffset){}

		double GetXOffset() const { return m_xOffset; }
		double GetYOffset() const { return m_yOffset; }

		SET_EVENT_TYPE(MouseScrolledEvent)
	private:
		double m_xOffset, m_yOffset;
	};

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(double xPos, double yPos) : m_xPos(xPos), m_yPos(yPos) {}

		double GetXPos() const { return m_xPos; }
		double GetYPos() const { return m_yPos; }

		SET_EVENT_TYPE(MouseMovedEvent)
	private:
		double m_xPos, m_yPos;
	};
}
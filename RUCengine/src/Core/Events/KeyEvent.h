#pragma once

#include "Event.h"

namespace RUC
{
	class KeyDownEvent : public Event
	{
	public:
		KeyDownEvent(int keyCode) : m_KeyCode(keyCode) {}

		int GetKeyCode() { return m_KeyCode; }

		SET_EVENT_TYPE(KeyDownEvent)
	private:
		int m_KeyCode;
	};

	class KeyUpEvent : public Event
	{
	public:
		KeyUpEvent(int keyCode) : m_KeyCode(keyCode) {}

		int GetKeyCode() { return m_KeyCode; }

		SET_EVENT_TYPE(KeyUpEvent)
	private:
		int m_KeyCode;
	};
}
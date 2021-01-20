#pragma once

#include "Event.h"

namespace RUC
{
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) : m_Event(event) {}
		
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.getEventType() == T::getStaticType())
			{
				m_Event.handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
}
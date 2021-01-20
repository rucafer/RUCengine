#pragma once

namespace RUC
{
#define SET_EVENT_TYPE(type) static EventType getStaticType() {return EventType::type; }\
							 EventType getEventType() override {return getStaticType(); }

	enum class EventType
	{
		WindowClosedEvent, WindowResizedEvent,
		MouseButtonUpEvent, MouseButtonDownEvent,
		MouseMovedEvent, MouseScrolledEvent,
		KeyDownEvent, KeyUpEvent
	};

	class Event
	{
	public:
		virtual ~Event() = default;

		virtual EventType getEventType() = 0;

		bool handled = false;
	};
}
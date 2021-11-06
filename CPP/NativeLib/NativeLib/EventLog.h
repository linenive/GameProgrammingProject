#pragma once
#include "Common.h"
#include "GameTime.h"

class EventLog : public Object {
	GODOT_CLASS(EventLog, Object)
private:
	Variant test;
	const string event_name;
	const string event_description;
	const Vector2* event_position;
	const GameTime occurrence_time;

public:
	EventLog(const string event_name, const string event_description, const Vector2* event_position)
		: event_name(event_name), event_description(event_description), event_position(event_position) {
		test = 145;
	}
	bool IsHavePositionData() {
		return event_position != nullptr;
	}
	const Vector2* GetPosition() {
		return event_position;
	}
	const string GetEventName() {
		return event_name;
	}
	const string GetEventDescription() {
		return event_description;
	}
	const GameTime GetOccurrenceTime() {

	}
	void _init(){}

	void _regeister_methods() {
		register_method("_init", &EventLog::_init);
	}
};
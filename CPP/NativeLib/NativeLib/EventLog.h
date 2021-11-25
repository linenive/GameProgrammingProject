#pragma once
#include "GameTime.h"

class EventLog {
private:
	string event_name;
	string event_description;
	Vector2 event_position;
	GameTime occurrence_time;

public:
	~EventLog() {
	}
	EventLog(string _event_name, string _event_description, GameTime(_occurrence_time))
		: event_name(_event_name), event_description(_event_description), occurrence_time(_occurrence_time),
		event_position(Vector2(-1, -1)) {}
	EventLog(string event_name, string event_description, GameTime(_occurrence_time),
		Vector2 event_position)
		: event_name(event_name), event_description(event_description), occurrence_time(_occurrence_time), 
		event_position(event_position) {}

	bool IsHaveValidPositionData() {
		return !(event_position.x == -1 && event_position.y == -1);
	}
	const Vector2 GetPosition() {
		return event_position;
	}
	const string GetEventName() {
		return event_name;
	}
	const string GetEventDescription() {
		return event_description;
	}
	GameTime GetOccurrenceTime() {
		return occurrence_time;
	}
};


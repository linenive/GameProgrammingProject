#pragma once
#include "GameTime.h"

class EventLog {
private:
	const string event_name;
	const string event_description;
	const Vector2* event_position;
	const GameTime occurrence_time;

public:
	~EventLog() {
		if (!IsHaveValidPositionData()) {
			delete event_position;
		}
	}
	EventLog(const string _event_name, const string _event_description, GameTime(_occurrence_time))
		: event_name(_event_name), event_description(_event_description), occurrence_time(_occurrence_time),
		event_position(new Vector2(-1, -1)) {}
	EventLog(const string event_name, const string event_description, GameTime(_occurrence_time),
		const Vector2* event_position)
		: event_name(event_name), event_description(event_description), occurrence_time(_occurrence_time), 
		event_position(event_position) {}

	bool IsHaveValidPositionData() {
		return !(event_position->x == -1 && event_position->y == -1);
	}
	const Vector2 GetPosition() {
		return *event_position;
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


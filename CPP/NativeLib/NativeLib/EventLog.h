#pragma once
#include "GameTime.h"
#include "SerializableClass.h"

class EventLog : SerializableClass{
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

	virtual Array Serialize() {
		Array serialized_event_log = Array();
		serialized_event_log.append(String(event_name.c_str()));
		serialized_event_log.append(String(event_description.c_str()));
		serialized_event_log.append(occurrence_time.GetYear().val);
		serialized_event_log.append(occurrence_time.GetMonth().val);
		serialized_event_log.append(occurrence_time.GetDay().val);
		serialized_event_log.append(occurrence_time.GetHour().val);
		serialized_event_log.append(occurrence_time.GetMinute().val);
		serialized_event_log.append(event_position);

		return serialized_event_log;
	}
};


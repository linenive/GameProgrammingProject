#pragma once
#include <list>
#include "Common.h"
#include "GameRule.h"
#include "EventLog.h"

class EventLogRepository {
private:
	int max_stack = EVENT_LOG_STACK_MAX;
	list<EventLog> logs;

	bool IsStackFull() {
		return logs.size() >= max_stack;
	}

public:
	void LoadData() {
		// To-do: 세이브파일에서 데이타 로드
	}

	void AddLog(EventLog new_log) {
		if (IsStackFull()) {
			logs.pop_front();
		}
		logs.push_back(new_log);
	}

	list<EventLog> GetEventLog() {
		return logs;
	}

	Array GetSerializedEventLogs() {
		Array serialized_event_logs = Array();
		for (auto log : logs) {
			serialized_event_logs.append(log.Serialize());
		}
		return serialized_event_logs;
	}
};
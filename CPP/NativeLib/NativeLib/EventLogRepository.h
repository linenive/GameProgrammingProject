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
	EventLogRepository() {
		// �׽�Ʈ�� �ӽ� ����Ÿ
		AddLog(EventLog("guest visited", "guest Warrior Jan visited.", nullptr));
		AddLog(EventLog("guest visited", "guest Mage Yo visited.", nullptr));
		AddLog(EventLog("guest visited", "guest Priest Jun visited.", nullptr));
	}
	void LoadData() {
		// To-do: ���̺����Ͽ��� ����Ÿ �ε�
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
};
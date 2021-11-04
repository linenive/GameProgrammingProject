#pragma once
#include "TimeRepository.h"
#include "EventLogRepository.h"

class GameWorldForUI {
public:
	virtual GameTime GetGameTime() = 0;
	virtual list<EventLog> GetEventLog() = 0;
};
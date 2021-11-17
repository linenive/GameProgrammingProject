#pragma once
#include "TimeRepository.h"

class GameWorldForEvent {
public:
	virtual TimeRepository* GetTimeRepository() = 0;
	virtual ObjectRepository* GetObjectRepository() = 0;
	virtual int GetRandomSeedByNowTime() = 0;
	virtual void AddEventLog(EventLog new_log) = 0;
};
#pragma once
#include "TimeRepository.h"

class GameWorldForProgressService {
public:
	virtual TimeRepository* GetTimeRepository() = 0;
	virtual ObjectRepository* GetObjectRepository() = 0;
	virtual int GetRandomSeedByNowTime() = 0;
	virtual void AddEventLog(EventLog new_log) = 0;
};
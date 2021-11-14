#pragma once
#include "TimeRepository.h"

class GameWorldForEvent {
public:
	virtual TimeRepository* GetTimeRepository() = 0;
	virtual int GetRandomSeedByNowTime() = 0;
};
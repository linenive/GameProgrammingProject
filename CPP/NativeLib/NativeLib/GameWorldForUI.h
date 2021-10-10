#pragma once
#include "TimeRepository.h"

class GameWorldForUI {
public:
	virtual GameTime GetGameTime() = 0;
};
#pragma once
#include "ObjectRepository.h"

class GameWorldForAI {
public:
	virtual ObjectRepository* GetObjectRepository() = 0;
};
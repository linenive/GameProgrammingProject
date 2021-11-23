#pragma once
#include "ObjectRepository.h"

class GameWorldForObjectService {
public:
	virtual ObjectRepository* GetObjectRepository() = 0;
};
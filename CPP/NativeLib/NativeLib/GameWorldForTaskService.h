#pragma once
#include "ObjectRepository.h"

class GameWorldForTaskService {
public:
	virtual TileRepository* GetTileMap() = 0;
};
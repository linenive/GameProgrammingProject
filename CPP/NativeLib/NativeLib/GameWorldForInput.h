#pragma once
#pragma once
#include "TileRepository.h"
#include "ObjectRepository.h"

class GameWorldForInput {
public:
	virtual TileRepository* GetTileMap() = 0;
	virtual ObjectRepository* GetObjectRepository() = 0;
};
#pragma once
#include "TileRepository.h"
#include "ObjectRepository.h"

class GameWorldForAI {
public:
	virtual ObjectRepository* GetObjectRepository() = 0;
	virtual TileRepository* GetTileMap() = 0;
};
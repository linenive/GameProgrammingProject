#pragma once
#include "TileRepository.h"
#include "ObjectRepository.h"
#include "VillageRepository.h"

class GameWorldForWorld {
public:
	virtual TileRepository* GetTileMap() = 0;
	virtual ObjectRepository* GetObjectRepository() = 0;
	virtual VillageRepository* GetVillageRepository() = 0;
};
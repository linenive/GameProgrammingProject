#pragma once
#include "GameWorldForUI.h"
#include "GameWorldForAI.h"
#include "GameWorldForWorld.h"
#include "GameWorldForInput.h"
#include "GameWorldForEvent.h"
#include <string>

class GameWorld :
	public GameWorldForUI, public GameWorldForAI,
	public GameWorldForWorld, public GameWorldForInput,
	public GameWorldForEvent{

private:
	TimeRepository time_repo;
	TileRepository tile_repo;
	ObjectRepository object_repo;
	VillageRepository village_repo;
	EventLogRepository event_log_repo;
	unsigned int random_seed;

	unsigned int ExtractSeed(string value) {
		unsigned int new_seed = 13;
		for (int i = 0; i < value.size(); i++)
			new_seed = 31 * new_seed + (int) value[i];
		return new_seed;
	}

public:
	GameWorld();
	virtual GameTime GetGameTime() { return time_repo.GetGameTime(); }
	virtual TimeRepository* GetTimeRepository() { return &time_repo; }
	virtual TileRepository* GetTileMap() { return &tile_repo; }
	virtual ObjectRepository* GetObjectRepository() { return &object_repo; }
	virtual VillageRepository* GetVillageRepository() { return &village_repo; }
	virtual EventLogRepository* GetEventLogRepository() { return &event_log_repo; }
};

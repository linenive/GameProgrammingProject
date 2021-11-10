#pragma once
#include "GameWorldForUI.h"
#include "GameWorldForAI.h"
#include "GameWorldForWorld.h"
#include "GameWorldForInput.h"

class GameWorld :
	public GameWorldForUI, public GameWorldForAI,
	public GameWorldForWorld, public GameWorldForInput {

private:
	TimeRepository time_repo;
	TileRepository tile_repo;
	ObjectRepository object_repo;
	VillageRepository village_repo;
	EventLogRepository event_log_repo;

public:
	GameWorld();
	virtual GameTime GetGameTime() { return time_repo.GetGameTime(); }
	virtual TileRepository* GetTileMap() { return &tile_repo; }
	virtual ObjectRepository* GetObjectRepository() { return &object_repo; }
	virtual VillageRepository* GetVillageRepository() { return &village_repo; }
	virtual EventLogRepository* GetEventLogRepository() { return &event_log_repo; }
	void update(float delta);
};
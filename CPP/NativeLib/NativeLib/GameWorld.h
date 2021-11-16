#pragma once
#include "GameWorldForUI.h"
#include "GameWorldForAI.h"
#include "GameWorldForWorld.h"
#include "GameWorldForInput.h"
#include "GameWorldForStaticUnit.h"

class GameWorld :
	public GameWorldForUI, public GameWorldForAI,
	public GameWorldForWorld, public GameWorldForInput,
	public GameWorldForStaticUnit {

private:
	TimeRepository time_repo;
	TileRepository tile_repo;
	ObjectRepository object_repo;
	VillageRepository village_repo;
	EventLogRepository event_log_repo;
	BuildingRepository building_repo;

public:
	GameWorld();
	virtual GameTime GetGameTime() { return time_repo.GetGameTime(); }
	//To-do 가능한 repository 직접 주지 않는 방향으로 개선.
	virtual TileRepository* GetTileMap() { return &tile_repo; }
	virtual ObjectRepository* GetObjectRepository() { return &object_repo; }
	virtual VillageRepository* GetVillageRepository() { return &village_repo; }
	virtual list<EventLog> GetEventLog() { return event_log_repo.GetEventLog(); }
	virtual Tile* GetTileByPos(int pos_x, int pos_y) { return tile_repo.GetTile(pos_x, pos_y); };
	virtual Building* GetBuildingById(int id) { return building_repo.GetBuildingById(id); }
	virtual void AddBuilding(Building* building) { building_repo.AddBuilding(building); }
	void update(float delta);
};
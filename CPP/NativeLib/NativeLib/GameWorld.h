#pragma once
#include "GameWorldForUI.h"
#include "GameWorldForAI.h"
#include "GameWorldForWorld.h"

class GameWorld :
	public GameWorldForUI, public GameWorldForAI, public GameWorldForWorld {

private:
	TimeRepository time_repo;
	WorldRepository world_repo;

public:
	GameWorld();
	virtual GameTime GetGameTime() { return time_repo.GetGameTime(); }
	virtual TileMap GetTileMap() { return world_repo.GetTileMap(); }
	void update(float delta);
};
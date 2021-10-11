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

public:
	GameWorld();
	virtual GameTime GetGameTime() { return time_repo.GetGameTime(); }
	virtual TileRepository* GetTileMap() { return &tile_repo; }
	virtual ObjectRepository* GetObjectRepository() { return &object_repo; }
	void update(float delta);
};
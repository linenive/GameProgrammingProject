#pragma once
#include "GameWorldForUI.h"
#include "GameWorldForAI.h"
#include "WorldRepository.h"

class GameWorld : public GameWorldForUI, public GameWorldForAI{

private:
	TimeRepository time_repo;
	WorldRepository world_repo;

public:
	GameWorld();
	virtual GameTime GetGameTime() { return time_repo.GetGameTime(); }
	void update(float delta);
};
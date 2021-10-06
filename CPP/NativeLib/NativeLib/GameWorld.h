#pragma once
#include "GameWorldForUI.h"
#include "GameWorldForAI.h"

class GameWorld : public GameWorldForUI, public GameWorldForAI{

private:
	TimeRepository time_repo;

public:
	GameWorld();
	virtual GameTime getGameTime() { return time_repo.GetGameTime(); }
	void update(float delta);
};
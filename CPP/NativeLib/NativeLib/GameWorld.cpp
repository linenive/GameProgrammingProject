#include "GameWorld.h"

GameWorld::GameWorld(){
	time_repo = TimeRepository();
	world_repo = WorldRepository();
}

void GameWorld::update(float delta)
{
	time_repo.TimeGo(delta);
}

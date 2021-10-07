#include "GameWorld.h"

GameWorld::GameWorld(){
	time_repo = TimeRepository();
}

void GameWorld::update(float delta)
{
	time_repo.TimeGo(delta);
}

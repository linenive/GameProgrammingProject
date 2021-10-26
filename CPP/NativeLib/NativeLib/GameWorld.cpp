#include "GameWorld.h"

GameWorld::GameWorld(){
	time_repo = TimeRepository();
	tile_repo = TileRepository();
	object_repo = ObjectRepository();
	village_repo = VillageRepository();
}

void GameWorld::update(float delta)
{
	time_repo.TimeGo(delta);

	//object_repo.PlushNumber();
}

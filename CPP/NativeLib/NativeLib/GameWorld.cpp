#include "GameWorld.h"

GameWorld::GameWorld(){
	time_repo = TimeRepository();
	tile_repo = TileRepository();
	object_repo = ObjectRepository();
	village_repo = VillageRepository();
	base_random_seed = ExtractSeed("banana");

}


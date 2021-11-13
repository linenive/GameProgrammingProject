#include "GameWorld.h"

GameWorld::GameWorld(){
	time_repo = TimeRepository();
	tile_repo = TileRepository();
	object_repo = ObjectRepository();
	village_repo = VillageRepository();
	random_seed = ExtractSeed("banana");

	printf("%u\n", random_seed);
}


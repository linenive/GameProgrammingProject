#include "WorldRepository.h"

WorldRepository::WorldRepository()
{
	tile_size_x = DEFAULT_TILE_X;
	tile_size_y = DEFAULT_TILE_Y;
	CreateTileMapTemp();
}

void WorldRepository::CreateTileMapTemp() {
	int i, j;
	for (j = 0; j < tile_size_y; j++) {
		for (i = 0; i < tile_size_x; i++) {
			Tile new_tile = Tile();
			Transform2D new_transform = Transform2D(real_t(.0), Vector2(real_t(.0), real_t(.0)));
			new_tile.SetTransform(new_transform);
			tile_map[j][i] = new_tile;
			
		}
	}
}
#include "TileMap.h"

Transform2D createTransform2D(float x, float y) {
	real_t rotation = real_t(.0);
	Vector2 position = Vector2(real_t(x), real_t(y));
	return Transform2D(rotation, position);
}

void TileMap::CreateTileMapTemp() {
	int i, j;
	for (j = 0; j < tile_size_y; j++) {
		for (i = 0; i < tile_size_x; i++) {
			Tile new_tile = Tile();

			float pos_x, pos_y;
			pos_x = MAP_START_POS_X + i * TILE_WIDTH + TILE_WIDTH/2;
			pos_y = MAP_START_POS_Y + j * TILE_HEIGHT + TILE_HEIGHT/2;

			new_tile.SetTransform(createTransform2D(pos_x, pos_y));
			tile_map[i+tile_size_x*j] = new_tile;
		}
	}
}
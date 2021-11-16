#include "TileRepository.h"

Transform2D createTransform2D(float x, float y) {
	real_t rotation = real_t(.0);
	Vector2 position = Vector2(real_t(x), real_t(y));
	return Transform2D(rotation, position);
}

void TileRepository::CreateTileMapTemp() {
	int i, j;
	for (j = 0; j < tile_size_y; j++) {
		for (i = 0; i < tile_size_x; i++) {
			float pos_x = MAP_START_POS_X + i * TILE_WIDTH + TILE_WIDTH / 2;
			float pos_y = MAP_START_POS_Y + j * TILE_HEIGHT + TILE_HEIGHT / 2;

			tile_map[i + tile_size_x * j] = new Tile(
				eTileType::TILE_EARTH, createTransform2D(pos_x, pos_y), Vector2(TILE_WIDTH, TILE_HEIGHT)
			);
		}
	}

	for (i = 227; i < 232; i++) {
		tile_map[i]->SetTileType(TileType(eTileType::TILE_RIVER));
	}

	tile_map[613]->SetTileType(TileType(eTileType::TILE_RIVER));
	tile_map[766]->SetTileType(TileType(eTileType::TILE_RIVER));

	for (i = 900; i < 1004; i++) {
		tile_map[i]->SetTileType(TileType(eTileType::TILE_OCEAN));
	}
}
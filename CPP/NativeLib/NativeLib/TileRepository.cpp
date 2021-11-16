#pragma once

#include "TileRepository.h"

void TileRepository::CreateTileMapTemp() {
	int i, j;
	for (j = 0; j < tile_size_y; j++) {
		for (i = 0; i < tile_size_x; i++) {
			float pos_x = MAP_START_POS_X + i * TILE_WIDTH + TILE_WIDTH / 2;
			float pos_y = MAP_START_POS_Y + j * TILE_HEIGHT + TILE_HEIGHT / 2;

			tile_map[i][j] = new Tile(
				SurfaceType(SURFACE_EARTH), pos_x, pos_y
			);
		}
	}

	for (i = 227; i < 232; i++) {
		tile_map[i / DEFAULT_TILE_NUMBER_X][i % DEFAULT_TILE_NUMBER_X]->SetSurfaceType(SurfaceType(SURFACE_RIVER));
	}

	tile_map[10][10]->SetSurfaceType(SurfaceType(SURFACE_RIVER));
	tile_map[20][30]->SetSurfaceType(SurfaceType(SURFACE_RIVER));

	for (i = 900; i < 1004; i++) {
		tile_map[i / DEFAULT_TILE_NUMBER_X][i % DEFAULT_TILE_NUMBER_X]->SetSurfaceType(SurfaceType(SURFACE_OCEAN));
	}
}
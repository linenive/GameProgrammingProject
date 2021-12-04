#pragma once
#include "TileRepository.h"

class MapCreateService {
private:
	TileRepository* tile_repo;
	void CreateTileMapTemp() {
		printf("createTileMap start\n");
		int i, j;
		for (j = 0; j < tile_repo->GetTileSizeY(); j++) {
			for (i = 0; i < tile_repo->GetTileSizeX(); i++) {
				float pos_x = MAP_START_POS_X + i * TILE_WIDTH + TILE_WIDTH / 2;
				float pos_y = MAP_START_POS_Y + j * TILE_HEIGHT + TILE_HEIGHT / 2;

				tile_repo->InitTile(i, j, SurfaceType(SURFACE_EARTH), Vector2(pos_x, pos_y));
			}
		}

		for (i = 227; i < 232; i++) {
			tile_repo->UpdateTileType(i / DEFAULT_TILE_NUMBER_X, i % DEFAULT_TILE_NUMBER_X, SurfaceType(SURFACE_RIVER));
		}

		tile_repo->UpdateTileType(10, 10, SurfaceType(SURFACE_RIVER));
		tile_repo->UpdateTileType(20, 30, SurfaceType(SURFACE_RIVER));

		for (i = 900; i < 1004; i++) {
			tile_repo->UpdateTileType(i / DEFAULT_TILE_NUMBER_X, i % DEFAULT_TILE_NUMBER_X, SurfaceType(SURFACE_OCEAN));
		}
		printf("createTileMap done\n");
	}
public:
	MapCreateService(TileRepository* _tile_repo) : tile_repo(_tile_repo) {
		CreateRandomMap();
	};
	void CreateRandomMap() {
		CreateTileMapTemp();
	}
};
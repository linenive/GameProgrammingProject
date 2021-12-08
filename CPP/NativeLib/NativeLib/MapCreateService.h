#pragma once
#include "TileRepository.h"
#include "StaticUnitService.h"

class MapCreateService {
private:
	StaticUnitService* static_unit_service;
	TileRepository* tile_repo;
	void CreateTileMapTemp() {
		int i, j;
		for (j = 0; j < tile_repo->GetTileSizeY(); j++) {
			for (i = 0; i < tile_repo->GetTileSizeX(); i++) {
				float pos_x = MAP_START_POS_X + i * TILE_WIDTH + TILE_WIDTH / 2;
				float pos_y = MAP_START_POS_Y + j * TILE_HEIGHT + TILE_HEIGHT / 2;

				tile_repo->InitTile(i, j, SurfaceType(SURFACE_EARTH), Vector2(pos_x, pos_y));
			}
		}

		for (j = 16; j < 20; j++) {
			for (i = 50; i < 100; i++) {
				tile_repo->UpdateTileType(Coordinates(i, j), SurfaceType(SURFACE_RIVER));
			}
		}

		for (j = 18; j < 22; j++) {
			for (i = 95; i < 120; i++) {
				tile_repo->UpdateTileType(Coordinates(i, j), SurfaceType(SURFACE_RIVER));
			}
		}

		for (j = 30; j < 35; j++) {
			for (i = 20; i < 25; i++) {
				tile_repo->UpdateTileType(Coordinates(i, j), SurfaceType(SURFACE_RIVER));
			}
		}

		for (j = 88; j < 96; j++) {
			for (i = 32; i < 40; i++) {
				tile_repo->UpdateTileType(Coordinates(i, j), SurfaceType(SURFACE_RIVER));
			}
		}
	}

	void CreateTrees() {
		int i, j;
		for (j = 30; j < 40; j++) {
			for (i = 35; i < 42; i++) {
				static_unit_service->CreateStructure(
					eStructureType::TREE, Coordinates(i, j)
				);
			}
		}
	}
public:
	MapCreateService(StaticUnitService* _static_unit_service, TileRepository* _tile_repo)
		: static_unit_service(_static_unit_service), tile_repo(_tile_repo) {
		CreateRandomMap();
	};
	void CreateRandomMap() {
		CreateTileMapTemp();
		CreateTrees();
	}
};
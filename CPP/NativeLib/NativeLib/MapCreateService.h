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

		for (i = 227; i < 232; i++) {
			tile_repo->UpdateTileType(Coordinates(i / DEFAULT_TILE_NUMBER_X, i % DEFAULT_TILE_NUMBER_X), SurfaceType(SURFACE_RIVER));
		}

		tile_repo->UpdateTileType(Coordinates(10, 10), SurfaceType(SURFACE_RIVER));
		tile_repo->UpdateTileType(Coordinates(20, 30), SurfaceType(SURFACE_RIVER));

		for (i = 900; i < 1004; i++) {
			tile_repo->UpdateTileType(Coordinates(i / DEFAULT_TILE_NUMBER_X, i % DEFAULT_TILE_NUMBER_X), SurfaceType(SURFACE_OCEAN));
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
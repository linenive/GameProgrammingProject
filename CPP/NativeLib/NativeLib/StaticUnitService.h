#pragma once

#include "Common.h"
#include "Base.h"
#include "BuildingType.h"
#include "CoordinatesSystem.h"
#include "TileRepository.h"
#include "BuildingRepository.h"
#include <Node.hpp>

class StaticUnitService {

private:
	TileRepository* tile_repository;
	BuildingRepository* building_repository;
	int next_building_id;
	int next_structure_id;

	int CreateBuilding_(eBuildingType type, Coordinates top_left_coordinates);
	void RegisterBlocksToWorld(int start_x, int start_y, vector< vector<eBlockType> >& blocks, Building* building);
	bool IsPlacablePosition_(int start_x, int start_y, vector< vector<eBlockType> >& blocks);
	void HideBuildingBlocks(Building* building);

	Tile* GetTile(int pos_x, int pos_y) { return tile_repository->GetTile(pos_x, pos_y); };
	Building* GetBuildingById(int id) { return building_repository->GetBuildingById(id); }
	void AddBuilding(Building* building) { building_repository->AddBuilding(building); }
	void DeleteBuildingFromWorld(int id) { building_repository->DeleteBuildingById(id); }

public:
	int CreateBuilding(int type, Vector2 top_left_tile_position);
	Building* CreateBluePrintBuilding(int type);
	void RegisterBlueprintBlocks(vector< vector<eBlockType> >& blocks, Building* building);
	bool IsPlacablePosition(int type, Vector2 top_left_tile_position);
	void DeleteBuildingById(int id);
	vector<Coordinates> GetBuildingBlocksCoordinatesById(int id);

	StaticUnitService(TileRepository* tile_repo, BuildingRepository* building_repo);
	StaticUnitService(TileRepository* tile_repo, BuildingRepository* building_repo, int start_building_id, int start_structur_id);
};
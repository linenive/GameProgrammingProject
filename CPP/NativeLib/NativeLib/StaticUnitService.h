#pragma once

#include "Common.h"
#include "Base.h"
#include "BuildingType.h"
#include "Building.h"
#include "CoordinatesSystem.h"
#include "GameManager.h"
#include <Node.hpp>

class StaticUnitService {

private:
	GameWorldForStaticUnit* game_world;
	int next_building_id;
	int next_structure_id;

	int CreateBuilding_(eBuildingType type, Coordinates top_left_coordinates);
	void RegisterBlocksToWorld(int start_x, int start_y, vector< vector<eBlockType> >& blocks, Building* building);
	bool IsPlacablePosition_(int start_x, int start_y, vector< vector<eBlockType> >& blocks);
	void HideBuildingBlocks(Building* building);

public:
	void SetGameWorld(GameWorldForStaticUnit* world);
	int CreateBuilding(int type, Vector2 top_left_tile_position);
	Building* CreateBluePrintBuilding(int type);
	void RegisterBlueprintBlocks(vector< vector<eBlockType> >& blocks, Building* building);
	bool IsPlacablePosition(int type, Vector2 top_left_tile_position);
	void DeleteBuildingById(int id);
	vector<Coordinates> GetBuildingBlocksCoordinatesById(int id);

	StaticUnitService();
	StaticUnitService(int start_building_id, int start_structur_id);
};
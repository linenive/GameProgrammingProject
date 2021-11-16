#pragma once

#include "Common.h"
#include "Base.h"
#include "BuildingType.h"
#include "Building.h"
#include "CoordinatesSystem.h"
#include "GameManager.h"
#include <Node.hpp>

class StaticUnitManager : public Node {
	GODOT_CLASS(StaticUnitManager, Node);

private:
	GameWorldForStaticUnit* game_world;
	void LoadGameWorld();
	int next_building_id;
	int next_structure_id;

	int CreateBuilding_(eBuildingType type, Coordinates top_left_coordinates);
	void RegisterBlocksToWorld(int start_x, int start_y, vector< vector<eBlockType> >& blocks, Building* building);
	bool IsPlacablePosition_(int start_x, int start_y, vector< vector<eBlockType> >& blocks);
	void DeleteBuilding(Building* building);

public:
	int CreateBuilding(int type, Vector2 top_left_tile_position);
	bool IsPlacablePosition(int type, Vector2 top_left_tile_position);
	void DeleteBuildingById(int id);
	void GetUpdateTileList(int id) {/*To-do*/ };

	StaticUnitManager();
	StaticUnitManager(int start_building_id, int start_structur_id);

	static void _register_methods();
	void _init();
	void _ready();
};

StaticUnitManager::StaticUnitManager() : StaticUnitManager(1, 1) {}
StaticUnitManager::StaticUnitManager(int start_building_id, int start_structur_id)
	: next_building_id(start_building_id), next_structure_id(start_structur_id) { }

int StaticUnitManager::CreateBuilding(int type, Vector2 top_left_tile_position) {
	return CreateBuilding_(static_cast<eBuildingType>(type), AbsolutePositionToCoordinates(top_left_tile_position));
}

int StaticUnitManager::CreateBuilding_(eBuildingType type, Coordinates top_left_coordinates) {
	int x = top_left_coordinates.x;
	int y = top_left_coordinates.y;

	BuildingData data = BuildingData(type);
	if (IsPlacablePosition_(x, y, data.blocks) == false)
		return -1;

	Building* new_building = new Building(
		next_building_id++,
		data.name,
		Rect2(x, y, data.width, data.height),
		data.slot_num);

	RegisterBlocksToWorld(x, y, data.blocks, new_building);

	game_world->AddBuilding(new_building);
	return new_building->id;
}

bool StaticUnitManager::IsPlacablePosition(int type, Vector2 top_left_tile_position) {
	Coordinates left_top_coordinates = AbsolutePositionToCoordinates(top_left_tile_position);
	BuildingData data = BuildingData(static_cast<eBuildingType>(type));
	return IsPlacablePosition_(left_top_coordinates.x, left_top_coordinates.y, data.blocks);
}

bool StaticUnitManager::IsPlacablePosition_(int start_x, int start_y, vector< vector<eBlockType> >& blocks) {
	for (int i = 0; i < blocks.size(); i++) {
		for (int j = 0; j < blocks[i].size(); j++) {
			Tile* tile = game_world->GetTileByPos(start_x + i, start_y + j);
			int level = BlockType::LevelOf(blocks[i][j]);

			if (tile->IsEmptyLayer(level) == false)
				return false;
		}
	}
	return true;
}

void StaticUnitManager::RegisterBlocksToWorld(int start_x, int start_y, vector< vector<eBlockType> >& blocks, Building* building) {
	for (int i = 0; i < blocks.size(); i++) {
		for (int j = 0; j < blocks[i].size(); j++) {
			Tile* tile = game_world->GetTileByPos(start_x + i, start_y + j);
			eBlockType& block_type = blocks[i][j];

			tile->SetBlock(
				BlockType::LevelOf(block_type),
				BlockType::NameOf(block_type), building
			);

			building->RegisterBlockInfo(j, i, BlockType::LevelOf(block_type));
		}
	}
}

void StaticUnitManager::DeleteBuildingById(int id) {
	Building* building = game_world->GetBuildingById(id);
	DeleteBuilding(building);
}

void StaticUnitManager::DeleteBuilding(Building* building) {
	for (auto block_info : building->blocks) {
		Tile* tile = game_world->GetTileByPos(block_info.x, block_info.y);
		tile->GetBlock(block_info.layer_level)->Disappear();
		//Delete from building repository
	}
}
#pragma once

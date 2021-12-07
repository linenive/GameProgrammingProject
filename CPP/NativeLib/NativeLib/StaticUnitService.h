#pragma once

#include "Common.h"
#include "Base.h"
#include "BuildingType.h"
#include "StructureRepository.h"
#include "StructureType.h"
#include "CoordinatesSystem.h"
#include "TileRepository.h"
#include "BuildingRepository.h"
#include <Node.hpp>

class StaticUnitService {

private:
	TileRepository* tile_repo;
	BuildingRepository* building_repo;
	StructureRepository* structure_rep;
	int next_unit_id;

	int CreateBuilding(eBuildingType type, Coordinates top_left_coordinates);
	void RegisterBlocksToWorld(int start_x, int start_y, vector< vector<eBlockType> >& blocks, StaticUnit* staticUnit);
	bool IsPlacablePosition(int start_x, int start_y, vector< vector<eBlockType> >& blocks);

	Tile* GetTile(int pos_x, int pos_y) { return tile_repo->GetTile(pos_x, pos_y); };
	void AddBuilding(Building* building) { building_repo->AddBuilding(building); }
	void AddStructure(Structure* structure) { structure_rep->AddStructure(structure); }
	void AddStructureToBuilding(Structure* structure);
	void DeleteBuildingFromWorld(int id) { 
		building_repo->DeleteBuildingById(id); 
	}
	void DeleteStructureFromWorld(int id) { 
		structure_rep->DeleteStructureById(id); 
	}
	bool IsBuilding(int id) {
		return building_repo->IsExistId(id);
	}
	bool IsStructue(int id) {
		return !IsBuilding(id);
	}

	Rect2 ConvertToOccupationArea(Coordinates top_left_coordinates, int width, int height);

public:
	int GetBuildingId(Vector2 position);
	int GetStructureId(Vector2 position);
	int CreateBuilding(int type, Vector2 top_left_tile_position);
	Building* CreateBluePrintBuilding(int type);
	Structure* CreateBluePrintStructure(int type);
	Building* GetBuildingById(int id) { return building_repo->GetBuildingById(id); }
	Structure* GetStructureById(int id) { return structure_rep->GetStructureById(id); }
	void RegisterBlueprintBlocks(vector< vector<eBlockType> >& blocks, Building* building);
	bool IsPlacablePosition(int type, Vector2 top_left_tile_position);
	bool IsStructurePlacablePosition(int type, Vector2 top_left_tile_position);
	void DeleteUnitById(int id);
	vector<Coordinates> GetBuildingBlocksCoordinatesById(int id);

	int CreateStructure(eStructureType type, Coordinates top_left_coordinates);
	int CreateStructure(int type, Vector2 top_left_tile_position);
	vector<int> GetBuildingInAreaList(Coordinates position1, Coordinates position2);
	vector<int> GetStructureInAreaList(Coordinates position1, Coordinates position2);
	Vector2 GetNearestStructurePos(Coordinates cur_position, eStructureType type);
	bool HasInventoryStructureInBuildingById(int id);
	bool HasInventoryStructureInBuilding(Building* building);
	Inventory* GetFirstInventoryInBuildingById(int id);
	Inventory* GetFirstInventoryInBuilding(Building* building);
	Array GetBuildingInfo(int buliding_id);
	Array GetStructureInfo(int structure_id);
	Array GetStructuresInfo();

	StaticUnitService(TileRepository* tile_repo, StructureRepository* structure_rep,
		BuildingRepository* building_repo);
	StaticUnitService(TileRepository* tile_repo, StructureRepository* structure_rep,
		BuildingRepository* building_repo, int start_unit_id);
};
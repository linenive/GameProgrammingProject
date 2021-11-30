#include "StaticUnitService.h"

StaticUnitService::StaticUnitService(TileRepository* tile_repo, BuildingRepository* building_repo)
	: StaticUnitService(tile_repo, building_repo, 1) {}
StaticUnitService::StaticUnitService(TileRepository* tile_repo, BuildingRepository* building_repo, int start_unit_id)
	: tile_repo(tile_repo), building_repo(building_repo), next_unit_id(start_unit_id) {}

int StaticUnitService::CreateBuilding(int type, Vector2 top_left_tile_position) {
	return CreateBuilding(static_cast<eBuildingType>(type), AbsolutePositionToCoordinates(top_left_tile_position));
}

int StaticUnitService::CreateBuilding(eBuildingType type, Coordinates top_left_coordinates) {
	int x = top_left_coordinates.x;
	int y = top_left_coordinates.y;

	BuildingData data = BuildingData(type);
	if (IsPlacablePosition(x, y, data.blocks) == false)
		return -1;

	Building* new_building = new Building(
		next_unit_id++,
		data.name,
		ConvertToOccupationArea(top_left_coordinates, data.width, data.height),
		data.slot_num);
	RegisterBlocksToWorld(x, y, data.blocks, new_building);

	AddBuilding(new_building);
	return new_building->id;
}

Rect2 StaticUnitService::ConvertToOccupationArea(Coordinates top_left_coordinates, int width, int height) {
	return Rect2(
		top_left_coordinates.x * TILE_WIDTH,
		top_left_coordinates.y * TILE_HEIGHT,
		width * TILE_WIDTH,
		height * TILE_HEIGHT
	);
}

int StaticUnitService::CreateStructure(int type, Vector2 top_left_tile_position) {
	return CreateStructure(static_cast<eStructureType>(type), AbsolutePositionToCoordinates(top_left_tile_position));
}

int StaticUnitService::CreateStructure(eStructureType type, Coordinates top_left_coordinates) {
	int x = top_left_coordinates.x;
	int y = top_left_coordinates.y;

	StructureData data = StructureData(type);
	if (IsPlacablePosition(x, y, data.blocks) == false)
		return -1;

	Structure* new_structure = new Structure(
		next_unit_id++,
		data.name,
		ConvertToOccupationArea(top_left_coordinates, data.width, data.height));

	RegisterBlocksToWorld(x, y, data.blocks, new_structure);

	AddStructure(new_structure);
	return new_structure->id;
}

Building* StaticUnitService::CreateBluePrintBuilding(int type) {
	BuildingData data = BuildingData((eBuildingType)type);

	Building* new_building = new Building(
		-1,
		data.name,
		Rect2(0, 0, data.width, data.height),
		data.slot_num);

	RegisterBlueprintBlocks(data.blocks, new_building);

	return new_building;
}

void StaticUnitService::RegisterBlueprintBlocks(vector< vector<eBlockType> >& blocks, Building* building) {
	for (int i = 0; i < blocks.size(); i++) {
		for (int j = 0; j < blocks[i].size(); j++) {
			eBlockType& block_type = blocks[j][i];

			// To-do: Blueprint가 delete되는 경우, 등록한 Block에 대해 delete해야 함.
			// 기존 Building과 다르므로 다른 처리가 필요함.
			Block* block = new Block(
				BlockTypeProperty::NameOf(block_type),
				Transform2D(0.0, Vector2(i * TILE_WIDTH, j * TILE_HEIGHT)),
				Vector2(TILE_WIDTH, TILE_HEIGHT)
			);
			block->block_type = block_type;
			building->RegisterBlock(block);
		}
	}
}

bool StaticUnitService::IsPlacablePosition(int type, Vector2 top_left_tile_position) {
	Coordinates left_top_coordinates = AbsolutePositionToCoordinates(top_left_tile_position);
	BuildingData data = BuildingData(static_cast<eBuildingType>(type));
	return IsPlacablePosition(left_top_coordinates.x, left_top_coordinates.y, data.blocks);
}

bool StaticUnitService::IsPlacablePosition(int start_x, int start_y, vector< vector<eBlockType> >& blocks) {
	for (int i = 0; i < blocks.size(); i++) {
		for (int j = 0; j < blocks[i].size(); j++) {
			Tile* tile = GetTile(start_x + i, start_y + j);
			int level = BlockTypeProperty::LevelOf(blocks[j][i]);

			if (tile->IsEmptyLayer(level) == false) {
				return false;
			}

		}
	}
	return true;
}

void StaticUnitService::RegisterBlocksToWorld(int start_x, int start_y, vector< vector<eBlockType> >& blocks, StaticUnit* staticUnit) {
	for (int i = 0; i < blocks.size(); i++) {
		for (int j = 0; j < blocks[i].size(); j++) {
			Tile* tile = GetTile(start_x + i, start_y + j);
			eBlockType& block_type = blocks[j][i];
			Block* block = tile->GetBlock(BlockTypeProperty::LevelOf(block_type));

			block->SetName(BlockTypeProperty::NameOf(block_type));
			block->block_type = block_type;
			block->owner_id = staticUnit->id;
			block->is_exist = true;
			block->SetPassSpeed(BlockTypeProperty::PassSpeedOf(block_type));

			staticUnit->RegisterBlock(
				tile->GetBlock(BlockTypeProperty::LevelOf(block_type))
			);
		}
	}
}

void StaticUnitService::DeleteUnitById(int id) {
	if (building_repo->IsExistId(id)) {
		DeleteBuildingFromWorld(id);
	}
	else if (structure_rep->IsExistId(id)) {
		DeleteStructureFromWorld(id);
	}
	else {
		printf("[StaticUnitService]ERROR: trying to delete not exsit unit.\n");
	}
}

vector<Coordinates> StaticUnitService::GetBuildingBlocksCoordinatesById(int id) {
	Building* building = GetBuildingById(id);
	vector<Coordinates> result;
	for (auto block : building->blocks) {
		result.push_back(
			AbsolutePositionToCoordinates(block->GetPhysics()->GetTransform())
		);
	}
	return result;
}

Array StaticUnitService::GetBuildingInfo(int id) {
	Building* building = GetBuildingById(id);
	return building->Serialize();
}

Array StaticUnitService::GetStructureInfo(int id) {
	Structure* structure = GetStructureById(id);
	return structure->Serialize();
}
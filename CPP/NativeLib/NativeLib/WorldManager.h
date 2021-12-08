#pragma once
#include "GameManager.h"
#include <Node.hpp>

class WorldManager : public Node {
	GODOT_CLASS(WorldManager, Node);

private:
	ObjectService* object_service;
	TileService* tile_service;
	VillageService* village_service;
	ResidentService* resident_service;
	void LoadGameWorld();
	bool IsCharacterNotExistError(int character_id) {
		if (object_service->IsCharacterNotExist(character_id)) {
			printf("WARNING: [WorldManager]trying to get not exist character! ");
			printf("input id : % d\n", character_id);
			return true;
		}
		return false;
	}

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _process(float delta);

	Vector2 GetTileCoordinate(Vector2 position) {
		Coordinates coord = tile_service->GetTileCoordinate(position);
		return Vector2(coord.x, coord.y);
	}

	float GetTilePassSpeed(Vector2 coordinate) {
		return tile_service->GetTilePassSpeed(Coordinates(coordinate.x, coordinate.y));
	}
	int GetTileSizeX() { return tile_service->GetTileSizeX(); }
	int GetTileSizeY() { return tile_service->GetTileSizeY(); }
	Transform2D GetSurfaceTransform(Vector2 coordinate) {
		return tile_service->GetSurface(coordinate.x, coordinate.y)->GetPhysics()->GetTransform();
	}
	Vector2 GetSurfaceScale(Vector2 coordinate) {
		return tile_service->GetSurface(coordinate.x, coordinate.y)->GetPhysics()->GetScale();
	}
	int GetSurfaceType(Vector2 coordinate) {
		return (int)tile_service->GetSurface(coordinate.x, coordinate.y)->GetSurfaceType().type;
	}
	String GetSurfaceName(Vector2 coordinate) {
		return String(tile_service->GetSurface(coordinate.x, coordinate.y)->GetName().c_str());
	}

	Array GetBlockTypes(Vector2 coordinate);

	int GetCharacterNumber() {
		return object_service->GetCharacterNumber();
	}
	Transform2D GetCharacterTransform(int character_id) {
		if (IsCharacterNotExistError(character_id)) {
			return Transform2D(0, Vector2(-1, -1));
		}
		return object_service->GetCharacter(character_id)->GetPhysics()->GetTransform();
	}
	Vector2 GetCharacterScale(int character_id) {
		if (IsCharacterNotExistError(character_id)) {
			return Vector2(0,0);
		}
		return object_service->GetCharacter(character_id)->GetPhysics()->GetScale();
	}

	Array GetCharacterInfo(int character_id) {
		return object_service->GetCharacter(character_id)->Serialize();
	}

	Vector2 GetWorldSize();

	String GetVillageName() {
		return String(village_service->GetVillageName());
	}

	void SetVillageName(String new_name) {
		village_service->SetVillageName(new_name);
	}

	int GetMoney() {
		return village_service->GetMoney();
	}

	Array GetRecruitableResidentArray() {
		return resident_service->GetRecruitableResidentArray();
	}
};
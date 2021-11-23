#pragma once
#include "CharacterFactory.h"

class ObjectService {
private:
	CharacterFactory factory = CharacterFactory();
	GameWorldForObjectService* game_world;
	ObjectRepository* object_repo;

public:
	queue<int> new_character_ids;
	ObjectService(GameWorldForObjectService* _game_world):game_world(_game_world){
		object_repo = _game_world->GetObjectRepository();
	}

	void TestNewCharacter(Transform2D transform) {
		WorldObject* new_character = factory.CreateObject(transform, Vector2(TILE_WIDTH, TILE_HEIGHT));
		object_repo->AddResident((Character*)new_character);
		// Godot::print("[ObjectRepository]TestNewCharacter: " + characters[0]->GetPhysics().GetPosition());
	}
	void CreateNewGuest() {
		Coordinates arrival_point = Coordinates(0, 15);
		WorldObject* new_character = factory.CreateObject(
			Transform2D(0, CoordinatesToCenterVector(arrival_point)),
			Vector2(TILE_WIDTH, TILE_HEIGHT)
		);
		object_repo->AddGuest((Character*)new_character);
		new_character_ids.push(object_repo->GetCharacterNumber() - 1);
		// Godot::print("[ObjectRepository]CreateNewGuest");
	}

	vector<Character*>* GetCharacters() {
		return game_world->GetObjectRepository()->GetCharacters();
	}
	vector<Character*>* GetGuests() {
		return game_world->GetObjectRepository()->GetGuests();
	}
	vector<Character*>* GetResidents() {
		return game_world->GetObjectRepository()->GetResidents();
	}
};
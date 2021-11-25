#pragma once
#include "CharacterFactory.h"
#include "ObjectRepository.h"

class ObjectService {
private:
	CharacterFactory factory = CharacterFactory();
	ObjectRepository* object_repo;
	int next_character_id; // save needed

public:
	queue<int> new_character_ids;
	queue<int> deleted_character_ids;
	ObjectService(ObjectRepository* _object_repo):object_repo(_object_repo){}

	void TestNewCharacter(Transform2D transform) {
		WorldObject* new_character = factory.CreateObject(
			next_character_id++, transform, Vector2(TILE_WIDTH, TILE_HEIGHT)
		);
		object_repo->AddResident((Character*)new_character);
		// Godot::print("[ObjectRepository]TestNewCharacter: " + characters[0]->GetPhysics().GetPosition());
	}
	void CreateNewGuest() {
		Coordinates arrival_point = Coordinates(0, 15);
		WorldObject* new_character = factory.CreateObject(
			next_character_id,
			Transform2D(0, CoordinatesToCenterVector(arrival_point)),
			Vector2(TILE_WIDTH, TILE_HEIGHT)
		);
		object_repo->AddGuest((Character*)new_character);
		new_character_ids.push(next_character_id);
		next_character_id++;
	}

	void DeleteChracter(int character_id) {
		object_repo->DeleteCharacter(character_id);
		deleted_character_ids.push(character_id);
	}

	map<int, Character*>* GetCharacters() {
		return object_repo->GetCharacters();
	}

	map<int, Character*>* GetGuests() {
		return object_repo->GetGuests();
	}

	map<int, Character*>* GetResidents() {
		return object_repo->GetResidents();
	}
	
	int GetCharacterNumber() {
		return object_repo->GetCharacterNumber();
	}

	Character* GetCharacter(int character_id) {
		return object_repo->GetCharacter(character_id);
	}
};
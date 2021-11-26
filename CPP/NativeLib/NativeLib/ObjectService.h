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
		WorldObject* new_character = factory.CreateCharacter(
			next_character_id++, transform
		);
		object_repo->AddResident((Character*)new_character);
		// Godot::print("[ObjectRepository]TestNewCharacter: " + characters[0]->GetPhysics().GetPosition());
	}
	Character* CreateNewGuest() {
		Coordinates arrival_point = Coordinates(0, 15);
		Character* new_character = factory.CreateCharacter(
			next_character_id,
			Transform2D(0, CoordinatesToCenterVector(arrival_point))
		);
		String s2 = String(new_character->GetFullName().GetFullname().c_str());
		Godot::print("[ObjectService]New Character " + s2 + " Created");
		object_repo->AddGuest(new_character);
		new_character_ids.push(next_character_id);
		next_character_id++;

		return (Character*)new_character;
	}

	void DeleteChracter(int character_id) {
		factory.ReturnCharacterName(object_repo->GetCharacter(character_id)->GetFullName());
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
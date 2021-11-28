#pragma once
#include "CharacterFactory.h"
#include "ObjectRepository.h"

class ObjectService {
private:
	CharacterFactory factory = CharacterFactory();
	ObjectRepository* object_repo;
	int next_character_id = 1; // save needed

public:
	queue<int> new_character_ids;
	queue<int> deleted_character_ids;
	ObjectService(ObjectRepository* _object_repo):object_repo(_object_repo){}

	Guest* CreateNewGuest() {
		Coordinates arrival_point = Coordinates(0, 15);
		Guest* new_guest = factory.CreateNormalGuest(
			next_character_id,
			Transform2D(0, CoordinatesToCenterVector(arrival_point))
		);
		object_repo->AddGuest(new_guest);
		new_character_ids.push(next_character_id);
		next_character_id++;

		return new_guest;
	}

	Resident* CreateNewResident(Character* guest) {

		Resident* new_resident = factory.CreateResident(
			next_character_id, guest
		);
		object_repo->AddResident(new_resident);
		new_character_ids.push(next_character_id);
		next_character_id++;

		return new_resident;
	}

	map<int, Character*>* GetCharacters() {
		return object_repo->GetCharacters();
	}

	map<int, Guest*>* GetGuests() {
		return object_repo->GetGuests();
	}

	map<int, Resident*>* GetResidents() {
		return object_repo->GetResidents();
	}

	void DeleteCharacter(int character_id) {
		factory.ReturnCharacterName(object_repo->GetCharacter(character_id)->GetFullName());
		object_repo->DeleteCharacter(character_id);
		deleted_character_ids.push(character_id);
	}
	
	int GetCharacterNumber() {
		return object_repo->GetCharacterNumber();
	}

	Character* GetCharacter(int character_id) {
		return object_repo->GetCharacter(character_id);
	}
};
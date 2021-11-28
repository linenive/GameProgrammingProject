#pragma once
#include <map>
#include "Character.h"

class ObjectRepository{
private:
	map<int, Character*> characters;
	map<int, Guest*> guests;
	map<int, Resident*> residents;

public:
	// To-do
	
	~ObjectRepository() {
		for (auto &kv : characters)
			delete kv.second;
		for (auto &kv : guests)
			delete kv.second;
		for (auto &kv : residents)
			delete kv.second;
	}

	bool IsNotExistId(int character_id) {
		return characters.find(character_id) == characters.end();
	}

	int GetCharacterNumber() {
		return (int) characters.size();
	}
	Character* GetCharacter(int character_id) {
		if (IsNotExistId(character_id)) {
			printf("WARNING: [ObjectRepository]trying to get not exist character! input id: %d\n", character_id);
			return nullptr;
		}
		return characters[character_id];
	}
	map<int, Character*>* GetCharacters() {
		return &characters;
	}
	map<int, Guest*>* GetGuests() {
		return &guests;
	}
	map<int, Resident*>* GetResidents() {
		return &residents;
	}

	bool AddGuest(Guest* new_character) {
		int character_id = new_character->GetId();

		if (IsNotExistId(character_id)) {
			printf("[ObjectRepository]AddGuest(id: %d)\n", character_id);
			characters[character_id] = new_character;
			guests[character_id] = new_character;
			return true;
		}
		else {
			printf("ERROR: [ObjectRepository]character id is duplicated! input id: %d\n", character_id);
			return false;
		}
	}

	bool AddResident(Resident* new_character) {
		int character_id = new_character->GetId();

		if (IsNotExistId(character_id)) {
			printf("[ObjectRepository]AddResident(id: %d)\n", character_id);
			characters[character_id] = new_character;
			residents[character_id] = new_character;
			return true;
		}
		else {
			printf("ERROR: [ObjectRepository]character id is duplicated! input id: %d\n", character_id);
			return false;
		}
	}

	bool DeleteCharacter(int character_id) {
		if (IsNotExistId(character_id)) {
			printf("ERROR: [ObjectRepository]trying to delete not exist character! input id: %d\n", character_id);
			return false;
		}
		delete characters[character_id];
		characters.erase(character_id);
		guests.erase(character_id);
		residents.erase(character_id);
		return true;
	}
};


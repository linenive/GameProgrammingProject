#pragma once
#include <map>
#include "Character.h"

// world object�� vector�� �����Ͽ����� ���� quad-tree �ڷᱸ���� �����غ���.
class ObjectRepository{
private:
	map<int, Character*> characters;
	map<int, Character*> guests;
	map<int, Character*> residents;
	bool IsExistId(int id) {
		return characters.find(id) != characters.end();
	}
	
public:
	// To-do
	
	~ObjectRepository() {
		map<int, Character*>::iterator it = characters.begin();
		for (auto &kv : characters)
			delete kv.second;
		for (auto &kv : guests)
			delete kv.second;
		for (auto &kv : residents)
			delete kv.second;
	}
	
	int GetCharacterNumber() {
		return (int) characters.size();
	}
	Character* GetCharacter(int character_id) {
		if (IsExistId(character_id)) {
			return characters[character_id];
		}
		else {
			printf("[ObjectRepository]ERROR: trying to get not exist character(input id: %d).\n", character_id);
		}
	}
	map<int, Character*>* GetCharacters() {
		return &characters;
	}
	map<int, Character*>* GetGuests() {
		return &guests;
	}
	map<int, Character*>* GetResidents() {
		return &residents;
	}

	void AddGuest(Character* new_character) {
		int character_id = new_character->GetId();

		if (IsExistId(character_id)) {
			printf("[ObjectRepository]ERROR: character id is duplicated(input id: %d).\n", character_id);
		}
		else {
			printf("[ObjectRepository]AddGuest(id: %d)\n", character_id);
			characters[character_id] = new_character;
			guests[character_id] = new_character;
		}
	}

	void AddResident(Character* new_character) {
		characters[new_character->GetId()] = new_character;
		residents[new_character->GetId()] = new_character;
	}

	bool DeleteCharacter(int id) {
		if (IsExistId(id)) {
			delete characters[id];
			characters.erase(id);
			guests.erase(id);
			residents.erase(id);
			return true;
		}
		else {
			printf("[ObjectRepository]ERROR: trying to delete not exist character(input id: %d).\n", id);
			return false;
		}
	}
};


#pragma once
#include <vector>
#include <queue>
#include "Character.h"

// world object�� vector�� �����Ͽ����� ���� quad-tree �ڷᱸ���� �����غ���.
class ObjectRepository{
private:
	vector<WorldObject*> stuffs;
	vector<Character*> characters;
	vector<Character*> guests;
	vector<Character*> residents;
	
public:
	// To-do
	
	ObjectRepository() {
	}
	~ObjectRepository() {
		for (auto e : stuffs)
			delete(e);
		for (auto e : characters)
			delete(e);
		for (auto e : guests)
			delete(e);
		for (auto e : residents)
			delete(e);
	}
	
	int GetCharacterNumber() {
		return characters.size();
	}
	Character* GetCharacter(int character_id) {
		return characters[character_id];
	}
	vector<Character*>* GetCharacters() {
		return &characters;
	}
	vector<Character*>* GetGuests() {
		return &guests;
	}
	vector<Character*>* GetResidents() {
		return &residents;
	}

	void AddGuest(Character* new_character) {
		characters.push_back((Character*)new_character);
		guests.push_back((Character*)new_character);
	}

	void AddResident(Character* new_character) {
		characters.push_back((Character*)new_character);
		residents.push_back((Character*)new_character);
	}
};


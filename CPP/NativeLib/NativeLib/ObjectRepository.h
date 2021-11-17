#pragma once
#include "CharacterFactory.h"
#include <vector>
#include <queue>

// world object�� vector�� �����Ͽ����� ���� quad-tree �ڷᱸ���� �����غ���.
class ObjectRepository{
private:
	CharacterFactory factory = CharacterFactory();

	vector<WorldObject*> stuffs;
	vector<Character*> characters;
	vector<Character*> guests;
	vector<Character*> residents;
	
public:
	// To-do
	queue<int> new_character_ids;
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
	void TestNewCharacter(Transform2D transform) {
		WorldObject* new_character = factory.CreateObject(transform, Vector2(TILE_WIDTH, TILE_HEIGHT));
		characters.push_back((Character*)new_character);
		residents.push_back((Character*)new_character);
		// Godot::print("[ObjectRepository]TestNewCharacter: " + characters[0]->GetPhysics().GetPosition());
	}
	void CreateNewGuest() {
		Coordinates arrival_point = Coordinates(0, 15);
		WorldObject* new_character = factory.CreateObject(
			Transform2D(0, CoordinatesToCenterVector(arrival_point)),
			Vector2(TILE_WIDTH, TILE_HEIGHT)
		);
		characters.push_back((Character*)new_character);
		guests.push_back((Character*)new_character);
		new_character_ids.push(characters.size() - 1);
		// Godot::print("[ObjectRepository]CreateNewGuest");
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
};


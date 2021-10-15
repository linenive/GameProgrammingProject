#pragma once
#include "CharacterFactory.h"
#include <vector>

// world object�� vector�� �����Ͽ����� ���� quad-tree �ڷᱸ���� ����غ���.
class ObjectRepository{
private:
	CharacterFactory factory = CharacterFactory();

	vector<WorldObject*> stuffs;
	vector<Character*> characters;
	int character_size;

public:
	ObjectRepository() {
		character_size = 0;
	}
	~ObjectRepository() {
		for (auto e : stuffs)
			delete(e);
		for (auto e : characters)
			delete(e);
	}
	void TestNewCharacter(Transform2D transform) {
		WorldObject* new_character = factory.createObject(transform, Vector2(TILE_WIDTH, TILE_HEIGHT));
		characters.push_back((Character*)new_character);
		character_size++;
		Godot::print(characters[0]->GetTransform());
	}
	int GetCharacterNumber() {
		return character_size;
	}
	Character GetCharacter(int character_id) {
		return *characters[character_id];
	}
};


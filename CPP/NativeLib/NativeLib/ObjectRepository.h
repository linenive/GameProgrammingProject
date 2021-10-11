#pragma once
#include "CharacterFactory.h"
#include <vector>

// world object를 vector로 구현하였으나 이후 quad-tree 자료구조를 고려해본다.
class ObjectRepository{
private:
	CharacterFactory factory = CharacterFactory();
	int test;

	vector<WorldObject*> stuffs;
	vector<WorldObject*> characters;

public:
	~ObjectRepository() {
		for (auto e : stuffs)
			delete(e);
		for (auto e : characters)
			delete(e);
	}
	void TestNewCharacter(Transform2D transform) {
		WorldObject* new_character = factory.createObject(transform);
		characters.push_back(new_character);
		Godot::print(characters[0]->GetTransform());
	}
	int GetCharacterNumber() {
		return characters.size();
	}
	Transform2D GetCharacterTransform(int i) {
		return characters[i]->GetTransform();
	}
};


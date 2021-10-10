#pragma once
#include "CharacterFactory.h"
#include <vector>

// world object�� vector�� �����Ͽ����� ���� quad-tree �ڷᱸ���� ����غ���.
class ObjectRepository{
private:
	CharacterFactory factory = CharacterFactory();
	int test=123;

	vector<WorldObject*> stuffs;
	vector<WorldObject*> characters;

public:
	void TestNewCharacter(Transform2D transform) {
		WorldObject new_character = factory.createObject(transform);
		characters.push_back(&new_character);

		test = 444;
	}
	int GetCharacterNumber() {
		return test;//characters.size();
	}
	void SetNumber() {
		test = 777;
	}
	Transform2D GetCharacterTransform(int i) {
		return characters[i]->GetTransform();
	}
};


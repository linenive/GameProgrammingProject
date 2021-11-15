#pragma once
#include "WorldObjectFactory.h"
#include "Character.h"

class PurposOfVisitFactory {
	PurposeOfVisit CreatePurposeOfVisit(PurposeOfVisitType type) {

	}
};

class CharacterFactory : public WorldObjectFactory {
private:
	void SettingPurposeOfVisit(Character* character) {
		Schedule* schedule = character->GetSchedule();
		schedule->
	}
protected:

public:
	WorldObject* CreateObject(Transform2D transform, Vector2 scale) {
		Character* new_character = new Character(transform, scale);
		

		return new_character;
	}
};
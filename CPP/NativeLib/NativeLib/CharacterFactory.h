#pragma once
#include <time.h>
#include "WorldObjectFactory.h"
#include "Character.h"
#include "NameGenerator.h"

// Todo: hard coding -> load DB
class PurposeOfVisitFactory {
public:
	PurposeOfVisit* CreatePurposeOfVisit(ePurposeOfVisitType type) {
		PurposeOfVisit* purpose;
		if (type == ePurposeOfVisitType::Lodge) {
			purpose = new PurposeOfVisit("Lodge", type);
		}
		else {
			purpose = new PurposeOfVisit("NoName", type);
		}
		return purpose;
	}
};

class CharacterFactory : public WorldObjectFactory {
private:
	NameGenerator name_generator;
	PurposeOfVisitFactory purpose_factory;
	// To-do: game progress에 따라 guest들이 가지는 number of purpose가 늘어나고,
	// purpose type들도 Unlock될 수 있도록 만든다.

	void SettingPurposeOfVisit(Character* character) {
		// To-do: number of purpose를 random으로 정하도록 바꾼다.
		int number_of_purpose = 2;
		for (int i = 0; i < number_of_purpose; i++) {
			GuestSchedule* schedule = (GuestSchedule*)character->GetSchedule();
			// To-do: Probability가 포함된 pool에서 random type을 pick하도록 바꾼다.
			// To-do: 한 번 picked 된 type은 delete in pool.
			schedule->AddPurposeOfVisit(purpose_factory.CreatePurposeOfVisit(ePurposeOfVisitType::Lodge));
		}
	}

public:

	Guest* CreateNormalGuest(int character_id, Transform2D transform) {
		Schedule* new_schedule = new GuestSchedule(Coordinates(0, 15), Coordinates(DEFAULT_TILE_NUMBER_X - 1, 30));
		srand((unsigned int)time(NULL));
		eGender gender = static_cast<eGender>(rand() % 2);
		Guest* new_character = new Guest(
			character_id, name_generator.MakeFullName(static_cast<eNameType>(gender)), gender,
			transform, Vector2(TILE_WIDTH, TILE_HEIGHT)
		);
		new_character->SetSchedule(new_schedule);

		return new_character;
	}

	Resident* CreateResident(int character_id, Character* guest) {
		Schedule* new_schedule = new ResidentSchedule();
		Resident* new_resident = new Resident(
			character_id, guest->GetFullName(), guest->GetGender(),
			guest->GetPhysics()->GetTransform(), guest->GetPhysics()->GetScale()
		);
		new_resident->SetSchedule(new_schedule);
		return new_resident;
	}

	void ReturnCharacterName(CharacterFullName fullName) {
		name_generator.ReturnName(fullName);
	}
};
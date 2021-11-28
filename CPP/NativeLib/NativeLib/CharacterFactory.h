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
	// To-do: game progress�� ���� guest���� ������ number of purpose�� �þ��,
	// purpose type�鵵 Unlock�� �� �ֵ��� �����.

	void SettingPurposeOfVisit(Character* character) {
		// To-do: number of purpose�� random���� ���ϵ��� �ٲ۴�.
		int number_of_purpose = 2;
		for (int i = 0; i < number_of_purpose; i++) {
			GuestSchedule* schedule = (GuestSchedule*)character->GetSchedule();
			// To-do: Probability�� ���Ե� pool���� random type�� pick�ϵ��� �ٲ۴�.
			// To-do: �� �� picked �� type�� delete in pool.
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
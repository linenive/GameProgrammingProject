#pragma once
#include "WorldObjectFactory.h"
#include "Character.h"

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
			schedule->AddPurposOfVisit(purpose_factory.CreatePurposeOfVisit(ePurposeOfVisitType::Lodge));
		}
	}

protected:

public:
	WorldObject* CreateObject(Transform2D transform, Vector2 scale) {
		Character* new_character = new Character(transform, scale);
		SettingPurposeOfVisit(new_character);
		return new_character;
	}
};
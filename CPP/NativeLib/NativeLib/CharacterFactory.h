#pragma once
#include "Base.h"
#include "WorldObjectFactory.h"
#include "Character.h"

class PurposeOfVisitFactory {
private:
	static string name[10];
	static string NameOf(ePurposeOfVisitType type) {
		return name[static_cast<int>(type)];
	};
	//To-do: init by external file
	static void Init() {
		name[static_cast<int>(ePurposeOfVisitType::Lodge)] = "Lodge";
		name[static_cast<int>(ePurposeOfVisitType::JustChilling)] = "JustChilling";
		name[static_cast<int>(ePurposeOfVisitType::Recovery)] = "Recovery";
		name[static_cast<int>(ePurposeOfVisitType::Cure)] = "Cure";
		name[static_cast<int>(ePurposeOfVisitType::Shopping)] = "Shopping";
		name[static_cast<int>(ePurposeOfVisitType::BuyLiquidMedicine)] = "BuyLiquidMedicine";
	}
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
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
	PurposeOfVisitFactory() {
		Init();
	}
	PurposeOfVisit* CreatePurposeOfVisit(ePurposeOfVisitType type) {
		PurposeOfVisit* purpose;
		purpose = new PurposeOfVisit(NameOf(type), type);
		return purpose;
	}	
};

class CharacterFactory : public WorldObjectFactory {
private:
	PurposeOfVisitFactory purpose_factory;
	// To-do: game progress에 따라 guest들이 가지는 number of purpose가 늘어나고,
	// purpose type들도 Unlock될 수 있도록 만든다.
	
	void SettingPurposeOfVisit(Character* character) {
		// To-do: number of purpose를 random으로 정하도록 바꾼다.
		int number_of_purpose = 2;
		for (int i = 0; i < number_of_purpose; i++) {
			GuestSchedule* schedule = (GuestSchedule *)character->GetSchedule();
			// To-do: Probability가 포함된 pool에서 random type을 pick하도록 바꾼다.
			// To-do: 한 번 picked 된 type은 delete in pool.
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
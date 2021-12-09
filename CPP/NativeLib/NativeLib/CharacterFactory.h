#pragma once
#pragma execution_character_set("utf-8")
#include <time.h>
#include "WorldObjectFactory.h"
#include "Character.h"
#include "NameGenerator.h"
#include "Random.h"

// Todo: hard coding -> load DB
class PurposeOfVisitFactory {
public:
	PurposeOfVisit* CreatePurposeOfVisit(ePurposeOfVisitType type) {
		PurposeOfVisit* purpose;
		if (type == ePurposeOfVisitType::BuyFirewood) {
			purpose = new PurposeOfVisit("장작 구매", type);
		}
		else if (type == ePurposeOfVisitType::JustChilling) {
			purpose = new PurposeOfVisit("그냥 휴식", type);
		}
		else if (type == ePurposeOfVisitType::BuyWoodenBow) {
			purpose = new PurposeOfVisit("나무 활 구매", type);
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
		int random_purpose = rand()%4;
		GuestSchedule* schedule = (GuestSchedule*)character->GetSchedule();
		if (random_purpose == 1) {
			schedule->AddPurposeOfVisit(purpose_factory.CreatePurposeOfVisit(ePurposeOfVisitType::JustChilling));
		}
		else if (random_purpose == 2) {
			schedule->AddPurposeOfVisit(purpose_factory.CreatePurposeOfVisit(ePurposeOfVisitType::BuyFirewood));
		}
		else if (random_purpose == 3) {
			schedule->AddPurposeOfVisit(purpose_factory.CreatePurposeOfVisit(ePurposeOfVisitType::BuyWoodenBow));
		}
	}

public:

	Guest* CreateNormalGuest(int character_id, CharacterSkill *start_skill) {
		Coordinates arrival_point = Coordinates(0, RandomNumberBetween(0, DEFAULT_TILE_NUMBER_X-1));
		Coordinates leave_point = Coordinates(DEFAULT_TILE_NUMBER_X - 1, RandomNumberBetween(0, DEFAULT_TILE_NUMBER_X-1));
		if (RandomNumberBetween(0,1)) {
			swap(arrival_point.x, leave_point.x);
			swap(arrival_point.y, leave_point.y);
		}
			
		if (RandomNumberBetween(0, 1)) {
			swap(arrival_point.x, arrival_point.y);
			swap(leave_point.x, leave_point.y);
		}
			
		Schedule* new_schedule = new GuestSchedule(arrival_point, leave_point);
		Transform2D transform = Transform2D(0, CoordinatesToCenterVector(arrival_point));
		srand((unsigned int)time(NULL));
		eGender gender = static_cast<eGender>(RandomNumberBetween(0, 1));
		Guest* new_character = new Guest(
			character_id, name_generator.MakeFullName(static_cast<eNameType>(gender)), gender,
			transform, Vector2(TILE_WIDTH, TILE_HEIGHT)
		);
		new_character->SetSchedule(new_schedule);
		SettingPurposeOfVisit(new_character);
		new_character->AddSkill(start_skill);
		return new_character;
	}

	Resident* CreateResident(int character_id, Character* guest) {
		Schedule* new_schedule = new ResidentSchedule();
		Resident* new_resident = new Resident(
			character_id, guest->GetFullName(), guest->GetGender(),
			guest->GetPhysics()->GetTransform(), guest->GetPhysics()->GetScale()
		);
		new_resident->SetSchedule(new_schedule);
		new_resident->CopyStat(&guest->base_stat);
		new_resident->CopySkill(guest->skill_list);
		return new_resident;
	}

	void ReturnCharacterName(CharacterFullName fullName) {
		name_generator.ReturnName(fullName);
	}
};
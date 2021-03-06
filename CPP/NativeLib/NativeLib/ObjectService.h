#pragma once
#include "CharacterFactory.h"
#include "ObjectRepository.h"
#include "SkillService.h"

class ObjectService {
private:
	CharacterFactory factory = CharacterFactory();
	ObjectRepository* object_repo;
	SkillService* skill_service;
	int next_character_id = 1; // save needed

public:
	queue<int> new_character_ids;
	queue<int> deleted_character_ids;
	ObjectService(ObjectRepository* _object_repo, SkillService* _skill_service)
		: object_repo(_object_repo), skill_service(_skill_service) {}

	int GetCharacterId(Vector2 position) {
		map<int, Character*>* characters = object_repo->GetCharacters();
		for (auto& kv : *characters) {
			if (kv.second->GetPhysics()->GetRect().has_point(position)) {
				return kv.first;
			}
		}
		return -1;
	}

	Guest* CreateNewGuest() {
		Guest* new_guest = factory.CreateNormalGuest(
			next_character_id,
			skill_service->PickRandomSkill()
		);
		object_repo->AddGuest(new_guest);
		new_character_ids.push(next_character_id);
		next_character_id++;

		return new_guest;
	}

	Resident* CreateNewResident(Character* guest) {

		Resident* new_resident = factory.CreateResident(
			next_character_id, guest
		);
		object_repo->AddResident(new_resident);
		new_character_ids.push(next_character_id);
		next_character_id++;

		return new_resident;
	}

	map<int, Character*>* GetCharacters() {
		return object_repo->GetCharacters();
	}

	void DeleteCharacter(int character_id) {
		if (object_repo->IsNotExistId(character_id)) {
			printf("WARNING: [ObjectService] Trying to delete not exist character. ");
			printf("id:% d\n", character_id);
			return;
		}
		factory.ReturnCharacterName(object_repo->GetCharacter(character_id)->GetFullName());
		deleted_character_ids.push(character_id);
		bool result = object_repo->DeleteCharacter(character_id);
	}

	bool IsCharacterNotExist(int character_id) {
		return object_repo->IsNotExistId(character_id);
	}
	
	int GetCharacterNumber() {
		return object_repo->GetCharacterNumber();
	}

	Character* GetCharacter(int character_id) {
		return object_repo->GetCharacter(character_id);
	}
};
#pragma once
#include "CharacterSkill.h"
#include "SkillRepository.h"
#include "PickRandom.h"
#include <vector>

class SkillService {
private:
	SkillRepository *repository;
public:
	CharacterSkill* PickRandomSkill();
	CharacterSkill* PickSkillByName(string name);
	void UnlockSkillWithEvent(eUnlockEvent event);

	SkillService(SkillRepository* _repository) {
		repository = _repository;
	}
};

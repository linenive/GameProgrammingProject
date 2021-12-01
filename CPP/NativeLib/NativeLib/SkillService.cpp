#include "SkillService.h"

CharacterSkill* SkillService::PickRandomSkill() {
	return &*select_randomly(repository->available_skill_list.begin(), repository->available_skill_list.end());
}

CharacterSkill* SkillService::PickSkillByName(string name) {
	for (CharacterSkill& skill : repository->all_skill_list) {
		if (skill.GetSkillName() == name)
			return &skill;
	}
	printf("ERROR: [SkillService] wrong skill name. %s\n", name);
	return &CharacterSkill("dummy", Stat());
}

void SkillService::UnlockSkillWithEvent(eUnlockEvent event) {
	repository->UnlockSkillWithEvent(event);
}
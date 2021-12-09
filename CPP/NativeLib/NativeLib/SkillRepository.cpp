#include "SkillRepository.h"

void SkillRepository::NewSkill(CharacterSkill skill) {
	all_skill_list.push_back(skill);
	available_skill_list.push_back(skill);
}

void SkillRepository::NewSkill(CharacterSkill skill, eUnlockEvent event) {
	all_skill_list.push_back(skill);
	event_skill_map[event].push_back(skill);
}

void SkillRepository::UnlockSkillWithEvent(eUnlockEvent event) {
	for (CharacterSkill skill : event_skill_map[event]) {
		available_skill_list.push_back(skill);
	}
}

SkillRepository::SkillRepository() {
	StatField::Init();
	NewSkill(Name("���� ����")
		.Add(eStatFieldType::BASE_MOVE_SPEED, 20));
	NewSkill(Name("����� ����")
		.Add(eStatFieldType::BASE_MOVE_SPEED, 40), eUnlockEvent::PASS_ONE_YEAR);
	NewSkill(Name("����")
		.Add(eStatFieldType::MAX_WEIGHT, 20));
	NewSkill(Name("���õ� ����")
		.Add(eStatFieldType::MAX_WEIGHT, 30)
		.Add(eStatFieldType::MOVE_SPEED_ON_HEAVY, 5), eUnlockEvent::PASS_ONE_YEAR);
	NewSkill(Name("���� �����")
		.Add(eStatFieldType::LOGGING_WORK_SPEED, 40)
		.Add(eStatFieldType::BASE_COMBAT_LEVEL, 10));
	NewSkill(Name("���� ������")
		.Add(eStatFieldType::LOGGING_WORK_SPEED, 60)
		.Add(eStatFieldType::BASE_COMBAT_LEVEL, 20));
	NewSkill(Name("���� �����")
		.Add(eStatFieldType::ITEM_CREATE_SPEED, 40));
	NewSkill(Name("���� ������")
		.Add(eStatFieldType::ITEM_CREATE_SPEED, 60));
}

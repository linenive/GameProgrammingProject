#pragma once
#include "Skill.h"
#include "SkillRepository.h"
#include "PickRandom.h"
#include <vector>

//TODO 싱글턴으로 만들기?
class SkillService {
private:
	SkillRepository repository;
public:
	Skill* PickRandomSkill();
	Skill* PickSkillByName(string name);
	void UnlockSkillWithEvent(eUnlockEvent event);
};


Skill *SkillService::PickRandomSkill() {
	return &*select_randomly(repository.available_skill_list.begin(), repository.available_skill_list.end());
}

Skill *SkillService::PickSkillByName(string name) {
	for (Skill& skill : repository.all_skill_list) {
		if (skill.GetSkillName() == name)
			return &skill;
	}
	//TODO error message
	return &Skill("dummy", Stat());
}

void SkillService::UnlockSkillWithEvent(eUnlockEvent event) {
	repository.UnlockSkillWithEvent(event);
}

void Example() {
	SkillService skill_service;

	cout << "hey" << endl;
	Skill* picked_skill = skill_service.PickSkillByName("FastWalk1");
	cout << picked_skill->GetSkillName() << endl;
	cout << picked_skill->stat.GetStatFieldValue(BASE_MOVE_SPEED) << endl;

	Skill* random_skill = skill_service.PickRandomSkill();
	cout << random_skill->GetSkillName() << endl;

	cout << skill_service.PickRandomSkill()->GetSkillName() << endl;
	cout << skill_service.PickRandomSkill()->GetSkillName() << endl;
	cout << skill_service.PickRandomSkill()->GetSkillName() << endl;

	skill_service.UnlockSkillWithEvent(eUnlockEvent::PASS_ONE_YEAR);
	cout << "\---pass one year!---\n" << endl;

	cout << skill_service.PickRandomSkill()->GetSkillName() << endl;
	cout << skill_service.PickRandomSkill()->GetSkillName() << endl;
	cout << skill_service.PickRandomSkill()->GetSkillName() << endl;

}
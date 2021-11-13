#pragma once
#include "Skill.h"
#include "UnlockEvent.h"
#include <string>
#include <vector>
#include <iostream>
#include <map>

class SkillRepository {
private:
	map< eUnlockEvent, vector<Skill> > event_skill_map;

	void NewSkill(Skill skill);
	void NewSkill(Skill skill, eUnlockEvent event);
	Skill Name(string name) { return Skill(name, Stat()); }

public:
	vector<Skill> all_skill_list;
	vector<Skill> available_skill_list;

	SkillRepository();
	void UnlockSkillWithEvent(eUnlockEvent event);
};

void SkillRepository::NewSkill(Skill skill) {
	all_skill_list.push_back(skill);
	available_skill_list.push_back(skill);
}

void SkillRepository::NewSkill(Skill skill, eUnlockEvent event) {
	all_skill_list.push_back(skill);
	event_skill_map[event].push_back(skill);
}

void SkillRepository::UnlockSkillWithEvent(eUnlockEvent event) {
	for (Skill skill : event_skill_map[event]) {
		available_skill_list.push_back(skill);
	}
}
/*
	 **스킬 종류 추가하는 공간**
	 bool 로 쓸건 value 1로 고정
*/

SkillRepository::SkillRepository() {
	NewSkill(Name("FastWalk1").Add(BASE_MOVE_SPEED, 5));
	NewSkill(Name("FastWalk2").Add(BASE_MOVE_SPEED, 10), eUnlockEvent::PASS_ONE_YEAR);
	NewSkill(Name("Carrier1").Add(MAX_WEIGHT, 20));
	NewSkill(Name("Carrier2").Add(MAX_WEIGHT, 30).Add(MOVE_SPEED_ON_HEAVY, 3), eUnlockEvent::PASS_ONE_YEAR);
	NewSkill(Name("SuperHuman").Add(BASE_MOVE_SPEED, 20).Add(BASE_WORK_SPEED, 10).Add(BASE_COMBAT_LEVEL, 5).Add(MAX_WEIGHT, 50).Add(CAN_WORK_UNTIL_MIDNIGHT, 1));
}

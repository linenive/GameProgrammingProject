#pragma once
#pragma execution_character_set("utf-8")

#include "CharacterSkill.h"
#include "UnlockEvent.h"
#include <string>
#include <vector>
#include <iostream>
#include <map>

class SkillRepository {
private:
	map< eUnlockEvent, vector<CharacterSkill> > event_skill_map;

	void NewSkill(CharacterSkill skill);
	void NewSkill(CharacterSkill skill, eUnlockEvent event);
	CharacterSkill Name(string name) { return CharacterSkill(name, Stat()); }

public:
	vector<CharacterSkill> all_skill_list;
	vector<CharacterSkill> available_skill_list;

	SkillRepository();
	void UnlockSkillWithEvent(eUnlockEvent event);
};

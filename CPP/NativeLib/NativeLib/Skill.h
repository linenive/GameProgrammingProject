#pragma once
#include "Stat.h"
#include <string>

using namespace std;

class Skill {
private:
	string skill_name;
public:
	Skill(string skill_name, Stat stat) : skill_name(skill_name), stat(stat) {}
	string GetSkillName() { return skill_name; }
	Skill& Add(eStatFieldName field_name, int field_value) {
		stat.AddStatFieldValue(field_name, field_value);
		return *this;
	}

	Stat stat;
};

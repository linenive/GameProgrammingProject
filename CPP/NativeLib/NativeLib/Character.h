#pragma once
#include "WorldObject.h"
#include "Inventory.h"
#include "Material.h"
#include "Schedule.h"
#include "CharacterSkill.h"
#include "Stat.h"
#include "CharacterName.h"
#include <vector>

enum eLevel {
	LEVEL1, LEVEL2, LEVEL3
};

enum eGender {
	MAN, WOMAN
};

class Character : public WorldObject {

private:
	int id;
	CharacterFullName full_name;
	Schedule* schedule;
	Inventory* inventory;
    eLevel level;
    eGender gender;
    vector<CharacterSkill> skill_list;
    Task* current_task;
    Stat base_stat;

    void SetRandomSkill();
    void AddSkill(CharacterSkill new_skill);
    void SwitchSkill(int old_skill_index, CharacterSkill new_skill);
    void SetBaseStat();

public:
	~Character() {
		delete schedule;
		delete inventory;
	}
	Character(int _id, CharacterFullName _name, eGender _gender,
		Transform2D transform, Vector2 scale)
		: id(_id), full_name(_name), gender(_gender),
		WorldObject("Noname", transform, scale){
		inventory = new Inventory();
		inventory->Get(new MaterialItem("Wood"));
	}

	void SetSchedule(Schedule* new_schedule){
		schedule = new_schedule;
	}
	
	Schedule* GetSchedule() { return schedule; }
	Inventory* GetInventory() {	return inventory; }
	int GetId() { return id; }
	CharacterFullName GetFullName() { return full_name; }
};
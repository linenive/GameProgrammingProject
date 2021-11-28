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

protected:
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

	int home_id = -1;
	int work_space_id = -1;

	~Character() {
		delete schedule;
		delete inventory;
	}
	Character(int _id, CharacterFullName _name, eGender _gender,
		Transform2D transform, Vector2 scale)
		: id(_id), full_name(_name), gender(_gender),
		WorldObject(_name.GetFullname(), transform, scale) {
		inventory = new Inventory();
		inventory->Get(new MaterialItem("Wood"));
	}
	Schedule* GetSchedule() { return schedule; }
	void SetSchedule(Schedule* new_schedule){
		schedule = new_schedule;
	}
	Inventory* GetInventory() {	return inventory; }
	int GetId() { return id; }
	string GetFirstName() { return full_name.GetName().value; }
	string GetLastName() { return full_name.GetLastname(); }
	CharacterFullName GetFullName() { return full_name; }
	eGender GetGender() { return gender; }
};

class Guest : public Character {
public:
	Guest(int _id, CharacterFullName _name, eGender _gender,
		Transform2D _transform, Vector2 _scale)
		: Character(_id, _name, _gender, _transform, _scale) {
		inventory = new Inventory();
		inventory->Get(new MaterialItem("Wood"));
	}

	GuestSchedule* GetSchedule() { return (GuestSchedule*)schedule; }
};

class Resident : public Character {
public:
	Resident(int _id, CharacterFullName _name, eGender _gender,
		Transform2D _transform, Vector2 _scale)
		: Character(_id, _name, _gender, _transform, _scale) {
		inventory = new Inventory();
		inventory->Get(new MaterialItem("Wood"));
	}
	
	ResidentSchedule* GetSchedule() { return (ResidentSchedule*)schedule; }
};

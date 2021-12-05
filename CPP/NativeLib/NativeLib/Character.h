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

    void SetRandomSkill();
    void SwitchSkill(int old_skill_index, CharacterSkill new_skill);
	void SetBaseStat() {
		for (auto &stat_field : base_stat.list) {
			if (static_cast<int>(stat_field.GetType()) < 400) { // normal ability
				stat_field.AddValue(100);
			}
		}
	}

public:

	int home_id = -1;
	int work_space_id = -1;
	Stat base_stat;
	vector<CharacterSkill*> skill_list;

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
		SetBaseStat();
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
	int GetStatValue(eStatFieldType type) {
		int result = base_stat.GetStatFieldValue(type);
		for (auto skill : skill_list) {
			result += skill->stat.GetStatFieldValue(type);
		}
		return result;
	}

	void CopyStat(Stat *other_stat) {
		base_stat = Stat(other_stat);
	}

	void CopySkill(vector<CharacterSkill*> &other_skill_list) {
		for (auto skill : other_skill_list) {
			skill_list.push_back(skill);
		}
	}

	void AddSkill(CharacterSkill *new_skill) {
		skill_list.push_back(new_skill);
	}

	virtual bool IsGuest() = 0;
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

	virtual bool IsGuest() { return true; }
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

	virtual bool IsGuest() { return false; }
};

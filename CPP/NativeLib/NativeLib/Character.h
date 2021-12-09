#pragma once
#pragma execution_character_set("utf-8")
#include "WorldObject.h"
#include "Inventory.h"
#include "Material.h"
#include "Schedule.h"
#include "CharacterSkill.h"
#include "Stat.h"
#include "CharacterName.h"
#include "ItemDictionary.h"
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
	void AddBaseItem() {
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
		inventory = new Inventory(2, 2);
		AddBaseItem();
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

	void AddItem(Item item) {
		AddItem(item, 1);
	}

	void AddItem(Item item, int amount) {
		inventory->AddItem(item, amount);
	}

	virtual bool IsGuest() = 0;

	virtual Array Serialize() {
		Array serialized_data = WorldObject::Serialize();
		serialized_data.append(id);
		serialized_data.append(full_name.GetLastname().c_str());
		serialized_data.append(full_name.GetName().value.c_str());
		switch (gender) {
		case eGender::MAN:
			serialized_data.append("남자");
			break;
		case eGender::WOMAN:
			serialized_data.append("여자");
			break;
		}
		serialized_data.append("마을 사람");
		serialized_data.append(physics->GetPosition());
		if (schedule->IsHavePurpose())
			serialized_data.append(schedule->GetFirstPurpose().c_str());
		else
			serialized_data.append("NONE");
		serialized_data.append(skill_list[0]->GetSkillName().c_str());

		return serialized_data;
	}

};

class Guest : public Character {
public:
	Guest(int _id, CharacterFullName _name, eGender _gender,
		Transform2D _transform, Vector2 _scale)
		: Character(_id, _name, _gender, _transform, _scale) {
		inventory = new Inventory(2, 2);
		AddBaseItem();
	}

	GuestSchedule* GetSchedule() { return (GuestSchedule*)schedule; }

	virtual bool IsGuest() { return true; }

	virtual Array Serialize() {
		Array serialized_data = Character::Serialize();
		int i;

		serialized_data.append(0);

		int inventory_size = inventory->GetSize();
		for (i = 0; i < inventory_size; i++) {
			Array item_data = Array();
			if (inventory->GetItemCountByIndex(i) > 0) {
				item_data.append(inventory->GetItemByIndex(i).GetName().c_str());
				item_data.append(inventory->GetItemByIndex(i).GetType().c_str());
				item_data.append(inventory->GetItemByIndex(i).GetID());
				item_data.append(inventory->GetItemCountByIndex(i));
			}
			serialized_data.append(item_data);
		}

		return serialized_data;
	}
};

class Resident : public Character {
public:
	Resident(int _id, CharacterFullName _name, eGender _gender,
		Transform2D _transform, Vector2 _scale)
		: Character(_id, _name, _gender, _transform, _scale) {
		inventory = new Inventory(2, 2);
		AddBaseItem();
	}
	
	ResidentSchedule* GetSchedule() { return (ResidentSchedule*)schedule; }

	virtual bool IsGuest() { return false; }

	virtual Array Serialize() {
		Array serialized_data = Character::Serialize();
		int i;

		serialized_data.append(1);

		int inventory_size = inventory->GetSize();
		for (i = 0; i < inventory_size; i++) {
			Array item_data = Array();
			if (inventory->GetItemCountByIndex(i) > 0) {
				item_data.append(inventory->GetItemByIndex(i).GetName().c_str());
				item_data.append(inventory->GetItemByIndex(i).GetType().c_str());
				item_data.append(inventory->GetItemByIndex(i).GetID());
				item_data.append(inventory->GetItemCountByIndex(i));
			}
			serialized_data.append(item_data);
		}

		return serialized_data;
	}
};

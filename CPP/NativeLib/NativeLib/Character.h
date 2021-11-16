#pragma once
#include "WorldObject.h"
#include "Task.h"
#include "Inventory.h"
#include "Material.h"
#include "Skill.h"
#include "Stat.h"
#include <vector>

using namespace beginner;

enum eLevel {
	LEVEL1, LEVEL2, LEVEL3
};

enum eGender {
	MAN, WOMAN
};

class Character : public WorldObject {

private:
	Task* currentTask;
	Inventory* inventory;
    eLevel level;
    eGender gender;
    vector<beginner::Skill> skill_list;
    Task* current_task;
    Stat base_stat;

    void SetRandomSkill();
    void AddSkill(beginner::Skill new_skill);
    void SwitchSkill(int old_skill_index, beginner::Skill new_skill);
    void SetBaseStat();

public:
	Character(Transform2D transform, Vector2 scale) : WorldObject("Noname", transform, scale), currentTask(nullptr){
		inventory = new Inventory();
		inventory->Get(new Material("Wood"));
	}
	
	Task* GetTask() { return currentTask; }
	void SetTask(Task* new_task) { currentTask = new_task; }
	bool HasTask() { return currentTask != nullptr; }

	Inventory* GetInventory() {	return inventory; }
};
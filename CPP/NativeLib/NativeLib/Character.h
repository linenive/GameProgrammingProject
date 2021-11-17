#pragma once
#include "WorldObject.h"
#include "Task.h"
#include "Inventory.h"
#include "Material.h"

class Character : public WorldObject {

private:
	Task* currentTask;
	Inventory* inventory;

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
#pragma once
#include "WorldObject.h"
#include "Inventory.h"
#include "Material.h"
#include "Schedule.h"

class Character : public WorldObject {

private:
	Schedule* schedule;
	Inventory* inventory;

public:
	~Character() {
		delete schedule;
		delete inventory;
	}
	Character(Transform2D transform, Vector2 scale) : WorldObject("Noname", transform, scale){
		inventory = new Inventory();
		inventory->Get(new Material("Wood"));
	}

	void SetSchedule(Schedule* new_schedule){
		schedule = new_schedule;
	}
	
	Schedule* GetSchedule() { return schedule; }
	Inventory* GetInventory() {	return inventory; }
};
#pragma once
#include "StaticUnit.h"
#include "StructureType.h"
#include "Inventory.h"

class Structure : public StaticUnit {
private:
	Inventory* inventory = nullptr;
public:
	eStructureType type;
	Structure(int id, eStructureType _type, string name, int build_cost, Rect2 _ocupation_area)
		: StaticUnit(id, name, build_cost, _ocupation_area), type(_type){}

	bool HasInventory() {
		return inventory != nullptr;
	}
	void CreateInventory() {
		inventory = new Inventory();
	}
	Inventory* GetInventory() {
		return inventory;
	}
};
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
	void CreateInventory(int size_x, int size_y) {
		inventory = new Inventory(size_x, size_y);
	}
	Inventory* GetInventory() {
		return inventory;
	}

	virtual Array Serialize() {
		Array serialized_data = StaticUnit::Serialize();
		serialized_data.append(static_cast<int>(type));
		serialized_data.append(static_cast<int>(HasInventory()));
		
		if (HasInventory()){
			int inventory_size = inventory->GetSize();

			for (int i = 0; i < inventory_size; i++) {
				Array item_data = Array();

				if (inventory->GetItemCountByIndex(i) > 0) {
					item_data.append(inventory->GetItemByIndex(i).GetName().c_str());
					item_data.append(inventory->GetItemByIndex(i).GetType().c_str());
					item_data.append(inventory->GetItemByIndex(i).GetID());
					item_data.append(inventory->GetItemCountByIndex(i));

				}

				serialized_data.append(item_data);
			}
		}
		
		return serialized_data;
	}
};
#pragma once
#include "Furniture.h"
#include "EquipItem.h"
#include <map>
#include <vector>

class DisplayStandItem : public FurnitureItem {
private:
	map<int, EquipItem*> display_slot;
	vector<eEquipItemType> display_type;

	int slot_current_count = 0;
	int slot_max_count;

	bool IsFullSlot() {
		return display_slot.size() == slot_max_count;
	}
	bool CanDisplayItemByIndex(int slot_index) {
		return display_slot.find(slot_index) == display_slot.end();
	}
public:
	~DisplayStandItem() {
	}
	DisplayStandItem(string name, int grade, int slot_count_max) : FurnitureItem(name, "DisplayStand", grade), slot_max_count(slot_max_count) {
		for (int i = 0; i < slot_count_max; i++) {
			display_slot.insert({ i, nullptr });
		}
	}
	void SetDisplayType(eEquipItemType new_display_type) {
		display_type.push_back(new_display_type);
	}
	EquipItem* SetSlotItem(EquipItem* new_item, int slot_index) {
		if (IsFullSlot()) return nullptr;

		EquipItem* last_item = display_slot[slot_index];
		display_slot[slot_index] = new_item;
		return last_item;
	}
	EquipItem* PopSlotItem(int slot_index) {
		if (CanDisplayItemByIndex(slot_index)) return nullptr;

		EquipItem* pop_item = display_slot[slot_index];
		display_slot[slot_index] = nullptr;
		slot_current_count--;

		return pop_item;
	}
	bool HasItem(string item_name) {
		for (int i = 0; i < slot_current_count; i++) {
			if (display_slot[i] != nullptr && display_slot[i]->GetName() == item_name) {
				return true;
			}
		}
		return false;
	}
};

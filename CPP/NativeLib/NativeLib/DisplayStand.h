#pragma once
#include "Furniture.h"
#include "StoreItem.h"
#include <map>

class DisplayStandItem : FurnitureItem {
private:
	map<int, StoreItem*> display_slot;
	int slot_current_count;
	int slot_max_count;

public:
	~DisplayStandItem() {
	}
	DisplayStandItem(string name, int grade, int slot_count_max) : FurnitureItem(name, grade), slot_max_count(slot_max_count) {
		slot_current_count = 0;
		for (int i = 0; i < slot_count_max; i++) {
			display_slot.insert({ i, nullptr });
		}
	}

	StoreItem* SetSlotItem(StoreItem* new_item, int slot_index) {
		if (display_slot.size() == slot_max_count) return nullptr;

		StoreItem* last_item = display_slot[slot_index];
		display_slot[slot_index] = new_item;
		return last_item;
	}
	StoreItem* PopSlotItem(int slot_index) {
		if (display_slot.find(slot_index) == display_slot.end()) return nullptr;

		StoreItem* pop_item = display_slot[slot_index];
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

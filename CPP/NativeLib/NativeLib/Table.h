#pragma once
#include "Furniture.h"
#include <map>

class TableItem : FurnitureItem {
private:
	map<int, Item*> table_slot;
	int slot_current_count;
	int slot_max_count;

public:
	~TableItem() {
	}
	TableItem(string name, int grade, int slot_count_max) : FurnitureItem(name, grade), slot_max_count(slot_max_count) {
		slot_current_count = 0;
		for (int i = 0; i < slot_count_max; i++) {
			table_slot.insert({ i, nullptr });
		}
	}

	Item* SetSlotItem(Item* new_item, int slot_index) {
		if (table_slot.size() == slot_max_count) return nullptr;

		Item* last_item = table_slot[slot_index];
		table_slot[slot_index] = new_item;
		return last_item;
	}
	Item* PopSlotItem(int slot_index) {
		if (table_slot.find(slot_index) == table_slot.end()) return nullptr;

		Item* pop_item = table_slot[slot_index];
		table_slot[slot_index] = nullptr;
		slot_current_count--;

		return pop_item;
	}
	bool HasItem(string item_name) {
		for (int i = 0; i < slot_current_count; i++) {
			if (table_slot[i] != nullptr && table_slot[i]->GetName() == item_name) {
				return true;
			}
		}
		return false;
	}

};

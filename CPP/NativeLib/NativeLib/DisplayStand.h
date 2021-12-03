#pragma once
#include "Furniture.h"
#include <unordered_map>

class DisplayStandItem : public FurnitureItem {
private:
	unordered_map<int, Item*> display_slot;

	int slot_current_count = 0;
	int slot_max_count;

	bool IsFullSlot() {
		return slot_current_count == slot_max_count;
	}
	bool CanDisplayItemByIndex(int slot_index) {
		return display_slot.find(slot_index) == display_slot.end();
	}
public:
	~DisplayStandItem() {
	}
	DisplayStandItem(string name, string type, int grade, int _slot_count_max) : FurnitureItem(name, type, grade), slot_max_count(_slot_count_max) {
		for (int i = 0; i < _slot_count_max; i++) {
			display_slot.insert({ i, nullptr });
		}
	}
	Item* SetSlotItem(Item* new_item, int slot_index) {
		Item* last_item = display_slot[slot_index];
		if (last_item == nullptr)	slot_current_count++;
		display_slot[slot_index] = new_item;
		return last_item;
	}
	Item* PopSlotItem(int slot_index) {
		if (CanDisplayItemByIndex(slot_index)) return nullptr;

		Item* pop_item = display_slot[slot_index];
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
	bool HasItem(int item_id) {
		for (int i = 0; i < slot_current_count; i++) {
			if (display_slot[i] != nullptr && display_slot[i]->GetID() == item_id) {
				return true;
			}
		}
		return false;
	}
};

#pragma once
#include "Furniture.h"
#include <unordered_map>

class DisplayStandItem : public FurnitureItem {
private:
	int slot_max_count;
public:
	~DisplayStandItem() {
	}
	DisplayStandItem(string name, string type, int grade, int _slot_count_max) : FurnitureItem(name, type, grade), slot_max_count(_slot_count_max) {
	}
	int GetSlotMaxCount() { return slot_max_count; }
};

#pragma once
#include "Item.h"
#include "GameRule.h"

class MaterialItem : public Item {

private:
	int item_count_now = 0;
	int item_count_max = MAX_ITEM_STACK;

public:
	MaterialItem(string name, unordered_map<string, int> param_list)
		: Item(name, "Material", param_list) {
		item_count_now = 1;
	}

	MaterialItem(string name, int item_count) : Item(name, "Material") {
		item_count_now = item_count;
	}
};
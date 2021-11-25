#pragma once
#include "Item.h"
#include "GameRule.h"

class MaterialItem : public Item {

private:
	int item_count_now = 0;
	int item_count_max = ITEM_STACK_MAX;

public:
	MaterialItem(string name) : Item(name, "Material") {
		item_count_now = 1;
	}

	MaterialItem(string name, int item_count) : Item(name, "Material") {
		item_count_now = item_count;
	}
};
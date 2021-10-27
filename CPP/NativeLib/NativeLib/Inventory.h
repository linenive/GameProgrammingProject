#pragma once
#include "Item.h"
#include "GameRule.h"

class Inventory {

private:
	Item* inventory[INVENTORY_X * INVENTORY_Y];
	int item_count = 0;

public:

	Item GetItem(int item_num) { return *inventory[item_num]; }
	
	void Get(Item* item) {
		if (item_count >= INVENTORY_X * INVENTORY_Y) {
			return;
		}

		inventory[item_count] = item;
		item_count++;
	}

	int GetSize() {
		return item_count;
	}
};
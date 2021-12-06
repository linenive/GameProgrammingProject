#pragma once
#include "Item.h"
#include "GameRule.h"
#include "CoordinatesSystem.h"

class InventorySlot {
public:
	Item item;
	int item_count = 0;

	bool operator <(InventorySlot& other) {
		if (item_count > 0 && other.item_count <= 0)
			return true;
		else if (item_count > 0 && other.item_count > 0)
			return item.GetID() < other.item.GetID();
		return false;
	}
};

class Inventory {
private:
	InventorySlot slots[INVENTORY_Y][INVENTORY_X];
	int slot_size;

	InventorySlot* SlotAt(Coordinates pos) {
		return &slots[pos.y][pos.x];
	}

	Coordinates BasePos() {
		return Coordinates(0, 0);
	}

	Coordinates InvalidPos() {
		return Coordinates(-1, -1);
	}

	Coordinates NextPos(Coordinates pos) {
		pos.x++;
		if (pos.x >= INVENTORY_X) {
			pos.y++;
			pos.x = 0;
		}
		if (pos.y >= INVENTORY_Y) {
			return InvalidPos();
		}
		return pos;
	}

	Coordinates IndexToPos(int index) {
		return Coordinates(index % INVENTORY_X, index / INVENTORY_X);
	}

	bool IsValidPos(Coordinates pos) {
		return pos.x >= 0 && pos.y >= 0 && pos.x < INVENTORY_X&& pos.y < INVENTORY_Y;
	}

	Coordinates GetItemPosByItemId(int id) {
		Coordinates cur_pos = BasePos();

		while (IsValidPos(cur_pos)) {
			if (SlotAt(cur_pos)->item.GetID() == id && SlotAt(cur_pos)->item_count >0) {
				return cur_pos;
			}
			cur_pos = NextPos(cur_pos);
		}
		return InvalidPos();
	}

	Coordinates GetItemPosToBeInserted(int id) {
		Coordinates pos = GetItemPosByItemId(id);
		if (IsValidPos(pos) && SlotAt(pos)->item_count < MAX_ITEM_STACK) {
			return pos;
		}
		else {
			return GetNextEmptyPos();
		}
	}

	Coordinates GetNextEmptyPos() {
		Coordinates cur_pos = BasePos();

		while (IsValidPos(cur_pos)) {
			if (SlotAt(cur_pos)->item_count == 0) {
				return cur_pos;
			}
			cur_pos = NextPos(cur_pos);
		}
		return InvalidPos();
	}

	void Sort() {
		vector <InventorySlot> flat_slot;
		Coordinates cur_pos = BasePos();

		while (IsValidPos(cur_pos)) {
			flat_slot.push_back(*SlotAt(cur_pos));
			cur_pos = NextPos(cur_pos);
		}
		sort(flat_slot.begin(), flat_slot.end());

		cur_pos = BasePos();
		int i = 0;
		while (IsValidPos(cur_pos)) {
			*SlotAt(cur_pos) = flat_slot[i];
			i++;
			cur_pos = NextPos(cur_pos);
		}
	}
public:
	void AddItem(Item item, int item_count) {
		while (item_count > 0) {
			Coordinates pos = GetItemPosToBeInserted(item.GetID());
			if (IsValidPos(pos)) {
				if (SlotAt(pos)->item_count == 0) {
					SlotAt(pos)->item = item;
				}
				int add_count = min(MAX_ITEM_STACK - SlotAt(pos)->item_count, item_count);
				SlotAt(pos)->item_count += add_count;
				item_count -= add_count;
			}
			else {
				//To-do make action when cannot some all items.
				return;
			}
		}
	}

	void PopItemById(int id, int item_count) {
		Coordinates pos = GetItemPosByItemId(id);
		if (IsValidPos(pos) > 0) {
			PopItemByPos(pos, item_count);
		}
	}

	void PopItemByPos(Coordinates pos, int item_count) {
		SlotAt(pos)->item_count -= item_count;
		if (SlotAt(pos)->item_count < 0) {
			printf("WARNING [Inventory] Try to pop item more than its count.\n");
			SlotAt(pos)->item_count = 0;
		}
		Sort();
	}

	//Get functions should used for get information, not for pop.
	Item GetItemById(int id) {
		return SlotAt(GetItemPosByItemId(id))->item;
	}

	Item GetItemByPos(Coordinates pos) {
		return SlotAt(pos)->item;
	}

	Item GetItemByIndex(int index) {
		return SlotAt(IndexToPos(index))->item;
	}

	int GetItemCount(Coordinates pos) {
		return SlotAt(pos)->item_count;
	}

	int GetItemCountByItemId(int id) {
		Coordinates pos = GetItemPosByItemId(id);
		if (IsValidPos(pos))
			return GetItemCount(pos);
		return 0;
	}

	int GetSize() {
		return 1;
		//return INVENTORY_Y * INVENTORY_X;
	}
};
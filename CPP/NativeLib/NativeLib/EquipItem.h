#pragma once
#include "Item.h"

enum class eEquipItemType {
	ARMOR, WEAPON, POTION
};

class EquipItem : public Item {

private:
	eEquipItemType equip_type;
public:
	EquipItem(string name, eEquipItemType equip_type) :Item(name, "EquipItem"),equip_type(equip_type) {}
	eEquipItemType GetEquipType() { return equip_type; }
};

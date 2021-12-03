#pragma once
#include "Item.h"
#include "Stat.h"

class EquipItem : public Item {

private:
	Stat stat;
public:
	EquipItem(string name, string type) :Item(name, type) { }

	void AddStat(eStatFieldType field_name, int field_value) {
		stat.AddStatFieldValue(field_name, field_value);
	}
};

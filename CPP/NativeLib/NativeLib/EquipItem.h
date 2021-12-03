#pragma once
#include "Item.h"
#include "Stat.h"

class EquipItem : public Item {

private:
	Stat stat;
public:
	EquipItem(string name, string type) :Item(name, type) { }

	Stat GetStat() { return stat; }
	void AddStat(eStatFieldType field_name, int field_value) {
		stat.AddStatFieldValue(field_name, field_value);
	}
	int GetStatValue(eStatFieldType stat_type) {
		StatField* stat_field = stat.FindStatField(stat_type);
		if (stat_field == nullptr) return -999;

		return stat_field->GetValue();
	}
};

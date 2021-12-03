#pragma once
#include "SaleItem.h"
#include "Stat.h"

class StatItem : public SaleItem {

private:
	Stat stat;
public:
	StatItem(string _name, string _type,int _price) :SaleItem(_name, _type, _price) { }

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

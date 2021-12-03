#pragma once
#include "SaleItem.h"
#include "Stat.h"

class StatItem : public SaleItem {

private:
	Stat stat;
public:
	StatItem(string _name, string _type, unordered_map<string, int> param_list) :Item(_name, _type, param_list) {
		string current_stat_key, current_value_key;

		for (int i = 1; i < param_list.size(); i ++) {
			current_stat_key = "stat_" + to_string(i);
			current_value_key = "stat_value_" + to_string(i);
			if (param_list.find(current_stat_key) == param_list.end()) break;
			if (param_list[current_stat_key]==-999) break;
			if (param_list[current_value_key] == -999) break;

			AddStat((eStatFieldType)param_list[current_stat_key], param_list[current_value_key]);
		}
	}

	Stat GetStat() { return stat; }

	void AddStat(eStatFieldType field_name, int field_value) {
		//printf("[%s] %d -> %d\n", GetName().c_str(), field_name, field_value);
		stat.AddStatFieldValue(field_name, field_value);
	}
	int GetStatValue(eStatFieldType stat_type) {
		StatField* stat_field = stat.FindStatField(stat_type);
		if (stat_field == nullptr) return -999;

		return stat_field->GetValue();
	}
};

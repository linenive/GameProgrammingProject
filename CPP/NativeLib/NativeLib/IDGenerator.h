#pragma once
#include <unordered_map>
#include <string>
#include "Common.h"
#include "GameRule.h"

class IDGenerator {
private:
	unordered_map<string, int> type_list;
	unordered_map<int, int> id_list;

	bool HasKeyInTypeList(string key) {
		return type_list.find(key) != type_list.end();
	}
	bool HasKeyInIDList(int key) {
		return id_list.find(key) != id_list.end();
	}
public:
	IDGenerator() {
		type_list["Material"] = 0;
		type_list["Furniture"] = 1;
		type_list["Bed"] = 1;
		type_list["DisplayStand"] = 1;
		type_list["Weapon"] = 2;
		type_list["Armor"] = 2;
		type_list["Potion"] = 2;

		for (auto elem : type_list) {
			id_list.insert(make_pair(elem.second, 1));
		}
	}
	int SetNewID(string type) {
		if (HasKeyInTypeList(type) == false) return -1;

		int type_key = type_list[type];
		if (HasKeyInIDList(type_key))
		{
			int current_id = id_list[type_key];
			id_list[type_key]++;
			return type_key * ID_CODE_DIGIT + current_id;
		}

		return -1;
	}
};
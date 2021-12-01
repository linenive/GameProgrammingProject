#pragma once
#include "IDRepository.h"
#include <unordered_map>
#include <string>

class IDService {
private:
	unordered_map<string, int> type_list;
	unordered_map<int, IDRepository> id_list;

	bool HasKeyInTypeList(string key) {
		return type_list.find(key) != type_list.end();
	}
	bool HasKeyInIDList(int key) {
		return id_list.find(key) != id_list.end();
	}
public:
	IDService(){
		type_list["Material"] = 0;
		type_list["Furnitual"] = 1;
		type_list["Bed"] = 2;
		type_list["DisplayStand"] = 3;
		
		for (auto elem : type_list) {
			id_list[elem.second] = IDRepository(elem.second);
		}
	}
	int SetNewID(string type) {
		if (HasKeyInTypeList(type) == false) return -1;

		int type_key = type_list[type];
		if (HasKeyInIDList(type_key)) 
			return id_list[type_key].GetNewID();

		return -1;
	}
};
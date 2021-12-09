#pragma once
#include <string>
#include <unordered_map>
#include "Common.h"

class Item  {

private:
	string name;
	string type;
protected:
	unordered_map<string, int> param_list;
public:	
	int id;
	bool operator <(const Item& other) const {
		return id < other.id;
	}

	string GetName() { return name; }
	void SetName(string name) { this->name = name; }

	string GetType() { return type; }
	void SetType(string type) { this->type = type; }

	int GetID() { return id; }
	void SetID(int _id) { id = _id; }

	Item() {}
	Item(string name, string type) : name(name), type(type) {}
	Item(string name, string type, unordered_map<string, int> param_list) : name(name), type(type), param_list(param_list){}

	int GetParameter(string key) {
		if (param_list.find(key) != param_list.end()) {
			return param_list[key];
		}
		return -999;
	}
};
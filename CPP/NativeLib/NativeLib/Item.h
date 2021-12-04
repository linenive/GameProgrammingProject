#pragma once
#include <string>
#include <unordered_map>
#include "Common.h"

class Item  {

private:
	string name;
	string type;
	int id;

protected:
	unordered_map<string, int> par_list;

public:
	string GetName() { return name; }
	void SetName(string name) { this->name = name; }

	string GetType() { return type; }
	void SetType(string type) { this->type = type; }

	int GetID() { return id; }
	void SetID(int _id) { id = _id; }

	Item() {}
	Item(string name, string type) : name(name), type(type) {}
	Item(string name, string type, unordered_map<string, int> par_list) : name(name), type(type), par_list(par_list){}

	int GetParameter(string key) {
		if (par_list.find(key) != par_list.end()) {
			return par_list[key];
		}
		return -999;
	}

};
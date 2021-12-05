#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include "ItemDictionary.h"

ItemDictionary* ItemDictionary::instance = NULL;
constexpr unsigned int HashCode(const char* str)
{
	return str[0] ? static_cast<unsigned int>(str[0]) + 0xEDB8832Full * HashCode(str + 1) : 8603;
}
vector<string> split(string input, char delimiter) {
	vector<string> answer;
	stringstream ss(input);
	string tmp;
	while (getline(ss, tmp, delimiter)) {
		answer.push_back(tmp);
	}
	return answer;
}
ItemDictionary* ItemDictionary::GetInstance() {
	if (instance == nullptr) instance = new ItemDictionary();
	return instance;
}
ItemDictionary::ItemDictionary() {
	id_maker = new IDGenerator();
	printf("generate item dictionary \n");
	GenerateDictionary();
}
void ItemDictionary::GenerateDictionary(){

	ifstream file(".data/Item_dictionary.csv");
	string line;
	int new_id;
	vector<string> sub_line;
	if (!file.is_open()) {
		printf("file error\n");
		return;
	}
	getline(file,line);
	key_list = split(line, ',');
	
	while (getline(file, line)) {
		sub_line = split(line, ',');
		if (sub_line.empty()) break;

		new_id = id_maker->SetNewID(sub_line[0]);
		
		Item* new_item = MakeItem(sub_line[0], sub_line);
		if (new_item == nullptr)	break;
		
		new_item->SetID(new_id);
		id_item_list[new_id] = new_item;
		name_item_list[sub_line[1]] = new_item;

		//printf("new item [%s , %s] key : %d\n", sub_line[1].c_str(), sub_line[0].c_str(), new_id);
	}
	file.close();
}

Item* ItemDictionary::MakeItem(string type, vector<string> sub_line_list){

	switch (HashCode(type.c_str())) {
		case HashCode("Material"):
			return new MaterialItem(sub_line_list[1]);
		case HashCode("Furniture"):
		case HashCode("Bed"):
		case HashCode("DisplayStand"):
			return new Item(sub_line_list[1], sub_line_list[0], ParameterParsing(sub_line_list));
		case HashCode("Weapon"):
		case HashCode("Armor"):
		case HashCode("Potion"): {
			return new StatItem(sub_line_list[1], sub_line_list[0], ParameterParsing(sub_line_list));
		}
		default:
			return new Item(sub_line_list[1], sub_line_list[0]);
	}
	return nullptr;
}

unordered_map<string, int> ItemDictionary::ParameterParsing(vector<string> sub_line_list){
	unordered_map<string, int> parameter_list;
	for (int i = 2; i < sub_line_list.size(); i++) {
		if (sub_line_list[i].empty()) {
			parameter_list[key_list[i]] = -999;
		}
		else {
			parameter_list[key_list[i]] = stoi(sub_line_list[i]);
		}
	}
	return parameter_list;
}

int ItemDictionary::GetIDByName(string name){
	auto find_item = name_item_list.find(name);
	if (find_item != name_item_list.end()) {
		return (find_item->second)->GetID();
	}
	return -1;
}
Item* ItemDictionary::GetItemByID(string name){
	auto find_item = name_item_list.find(name);
	if (find_item != name_item_list.end()) {
		return find_item->second;
	}
	return nullptr;
}

Item* ItemDictionary::GetItemByName(string name) {
	auto find_item = name_item_list.find(name);
	if (find_item != name_item_list.end()) {
		return find_item->second;
	}
	return nullptr;
}


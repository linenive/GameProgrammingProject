#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include "ItemDictionaryService.h"

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
void ItemDictionaryService::SetDictionary(){

	ifstream file(".data/Item_dictionary.csv");
	string line;
	int new_id;
	vector<string> sub_line;
	if (!file.is_open()) {
		printf("file error\n");
		return;
	}
	getline(file,line);
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

Item* ItemDictionaryService::MakeItem(string type, vector<string> sub_line_list){
	switch (HashCode(type.c_str())) {
		case HashCode("Material"):
			return new MaterialItem(sub_line_list[1]);
		case HashCode("Furniture"):
		case HashCode("Bed"):
			return new FurnitureItem(sub_line_list[1], sub_line_list[0], stoi(sub_line_list[2]));
		case HashCode("DisplayStand"):
			return new DisplayStandItem(sub_line_list[1], sub_line_list[0], stoi(sub_line_list[2]), stoi(sub_line_list[3]));
		case HashCode("Weapon"):
		case HashCode("Armor"):
		case HashCode("Potion"): {
			StatItem* new_item = new StatItem(sub_line_list[1], sub_line_list[0], stoi(sub_line_list[2]));
			StatParsing(new_item, sub_line_list);
			return new_item;
		}
		default:
			return new Item(sub_line_list[1], sub_line_list[0]);
	}
	return nullptr;
}

void ItemDictionaryService::StatParsing(StatItem* item, vector<string> sub_line_list){
	int size = sub_line_list.size();
	for (int i = 3; i < size; i += 2) {
		if (sub_line_list[i].empty()) break;
		if (i + 1 >= size || sub_line_list[i + 1].empty()) break;
		//printf("%s :: add stat %s, %d\n", item->GetName().c_str(), sub_line_list[i].c_str(), stoi(sub_line_list[i + 1]));
		item->AddStat((eStatFieldType)stoi(sub_line_list[i]), stoi(sub_line_list[i + 1]));
	}
}

int ItemDictionaryService::GetIDByName(string name){
	auto find_item = name_item_list.find(name);
	if (find_item != name_item_list.end()) {
		return (find_item->second)->GetID();
	}
}
Item* ItemDictionaryService::GetItemByID(string name){
	auto find_item = name_item_list.find(name);
	if (find_item != name_item_list.end()) {
		return find_item->second;
	}
}

Item* ItemDictionaryService::GetItemByName(string name){
	auto find_item = name_item_list.find(name);
	if (find_item != name_item_list.end()) {
		return find_item->second;
	}
}

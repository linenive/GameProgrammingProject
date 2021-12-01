#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "IDService.h"
#include "Item.h"

class ItemDictionary {
private:
	IDService* id_maker;
	unordered_map<int, Item> id_item_list;

	unordered_map<string, Item> name_item_list;
public:
	ItemDictionary(IDService* id_service):id_maker(id_service){
		int new_id = 0;

		new_id = id_maker->SetNewID("Material");
		Item new_item = Item("wood","Material");
		new_item.SetID(new_id);
		id_item_list[new_id] = new_item;

		name_item_list["wood"] = new_item;
		printf("new item wood key : %f", new_id);

		new_id = id_maker->SetNewID("Furnitual");
		Item new_item = Item("chair", "Furnitual");
		new_item.SetID(new_id);
		id_item_list[new_id] = new_item;

		name_item_list["chair"] = new_item;
		printf("new item hair key : %f", new_id);
	}

	int GetIDByName(string name) {
		auto find_item = name_item_list.find(name);
		if (find_item != name_item_list.end()) {
			return find_item->second.GetID();
		}
	}
	Item GetItemByID(string name) {
		auto find_item = name_item_list.find(name);
		if (find_item != name_item_list.end()) {
			return find_item->second;
		}
	}
	Item GetItemByName(string name) {
		auto find_item = name_item_list.find(name);
		if (find_item != name_item_list.end()) {
			return find_item->second;
		}
	}
};
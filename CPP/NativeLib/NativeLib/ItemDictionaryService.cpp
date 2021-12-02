#pragma once
#include <vector>
#include "ItemDictionaryService.h"

void ItemDictionaryService::SetDictionary(){

	//to do -> csv file read
	AddDictionary("wood", "Material");
	AddDictionaryFurniture("chair", "Furniture",3);
	AddDictionaryDisplayStand("weapon_display_stand", "DisplayStand",3,2);

}
void ItemDictionaryService::AddDictionary(string name, string type){
	int new_id = id_maker->SetNewID(type);
	Item new_item = Item(name, type);
	new_item.SetID(new_id);
	id_item_list[new_id] = &new_item;

	name_item_list[name] = &new_item;
	printf("new item %s key : %f",name, new_id);
}
void ItemDictionaryService::AddDictionaryFurniture(string name, string type, int grade) {
	int new_id = id_maker->SetNewID(type);
	FurnitureItem new_item = FurnitureItem(name, type,grade);
	new_item.SetID(new_id);
	id_item_list[new_id] = &new_item;

	name_item_list[name] = &new_item;
	printf("new furniture item %s key : %f", name, new_id);
}
void ItemDictionaryService::AddDictionaryDisplayStand(string name, string type, int grade, int slot_max_count) {
	int new_id = id_maker->SetNewID(type);
	DisplayStandItem new_item = DisplayStandItem(name, type, grade, slot_max_count);
	new_item.SetID(new_id);
	id_item_list[new_id] = &new_item;

	name_item_list[name] = &new_item;
	printf("new display stand item %s key : %f", name, new_id);
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

#pragma once

#include "StaticUnit.h"
#include "CharacterSlot.h"
#include "BuildingRole.h"
#include <vector>

using namespace std;

class Building : public StaticUnit {
private:
    int number_of_guests_per_month = 0;
    int cumulative_number_of_guests = 0;
public:
    int character_slot_num;
    vector<CharacterSlot*> character_slots;
    eBuildingRole building_role;
    list<int> inside_structures_list;
    
    Building(int _id, string _name, Rect2 _ocupation_area, int _character_slot_num, eBuildingRole _building_role)
        : StaticUnit(_id, _name, _ocupation_area), 
        character_slot_num(_character_slot_num), building_role(_building_role) { }

    ~Building() {
        for (auto slot : character_slots) {
            delete(slot);
        }
    }

    void AssignCharacter(Character* character) {
        if (IsAssignable()) {
            character_slots.push_back(new CharacterSlot(character));
        }
        else {
            printf("WARNING: [Building]trying to assigned resident to full building.\nbuilding_id = %d\n", id);
        }
    }

    void IncreaseOneVisits() {
        number_of_guests_per_month++;
        cumulative_number_of_guests++;
    }
    void FreeResident(int resident_id) {
        for (int i = 0; i < character_slots.size(); i++) {
            CharacterSlot* slot = character_slots[i];
            if (slot->GetCharacterId() == resident_id) {
                delete(character_slots[i]);
                character_slots.erase(character_slots.begin()+i);
                return;
            }
        }
        printf("WARNING: [Building]trying to free unassigned resident.\n");
        printf("building_id = %d, character_id = %d\n", id, resident_id);
    }

    bool IsAssignable() {
        return character_slots.size() < character_slot_num;
    }

    bool IsHouse() {
        return building_role == eBuildingRole::HOUSE;
    }

    bool IsWorkSpace() {
        return !IsHouse();
    }

    void AddStructureId(int id) {
        inside_structures_list.push_back(id);
    }

    virtual Array Serialize() { //id, name, character_slot_num, char1_id, char2_id, ...
        Array serialized_data = StaticUnit::Serialize();
        serialized_data.append(static_cast<int>(building_role));
        serialized_data.append(number_of_guests_per_month);
        serialized_data.append(cumulative_number_of_guests);
        serialized_data.append(character_slot_num);
        for (int i = 0; i < character_slot_num; i++) {
            if (i < character_slots.size()) {
                serialized_data.append(character_slots[i]->GetCharacterId());
            }
            else {
                serialized_data.append(-1);
            }
        }
        return serialized_data;
    }
};
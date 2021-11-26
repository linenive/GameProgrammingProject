#pragma once

#include "Building.h"
#include "Base.h"
#include <map>

class BuildingRepository {
private:
    map<int, Building*> building_map; // building_map[id] = building;
public:
    void AddBuilding(Building* building) {
        if (IsExistId(building->id)) {
            printf("[BuildingRepository]ERROR: building id is duplicated.\n");
        }
        else {
            building_map[building->id] = building;
        }
    }
    void DeleteBuildingById(int id) {
        if (IsExistId(id)) {
            Building* building = building_map[id];

            if (!building->character_slots.empty()) {
                printf("[BuildingRepository]WARNING: please free residents before delete building.\n");
                return;
            }

            for (auto block : building->blocks) {
                block->Disappear();
            }

            delete(building);
            building_map.erase(id);
        }
        else {
            printf("[BuildingRepository]WARNING: trying to delete not exist building.\n");
        }
    }
    Building* GetBuildingById(int id) {
        if (IsExistId(id)) {
            return building_map[id];
        }
        else {
            printf("[BuildingRepository]ERROR: trying to get not exist building.\n");
        }
    }
    bool IsExistId(int id) {
        return building_map.find(id) != building_map.end();
    }

    ~BuildingRepository() {
        for (auto item : building_map) {
            delete(item.second);
        }
    }
};

#pragma once

#include "Building.h"
#include "Base.h"
#include <map>

class BuildingRepository {
private:
    map<int, Building*> building_map;
public:
    void AddBuilding(Building* building) {
        if (IsExistId(building->id)) {
            printf("ERROR: [BuildingRepository]building id is duplicated. id = %d\n", building->id);
        }
        else {
            building_map[building->id] = building;
        }
    }
    void DeleteBuildingById(int id) {
        if (IsExistId(id)) {
            Building* building = building_map[id];

            if (!building->character_slots.empty()) {
                printf("WARNING: [BuildingRepository] please free residents before delete building. ");
                printf("id = %d\n", id);
                return;
            }

            for (auto block : building->blocks) {
                block->Disappear();
            }

            delete(building);
            building_map.erase(id);
        }
        else {
            printf("WARNING: [BuildingRepository]trying to delete not exist building. ");
            printf("id = %d\n", id);
        }
    }
    Building* GetBuildingById(int id) {
        if (IsExistId(id)) {
            return building_map[id];
        }
        else {
            printf("ERROR: [BuildingRepository]trying to get not exist building. ");
            printf("id = %d\n", id);
            return nullptr;
        }
    }

    Building* GetBuildingByArea(Rect2 area) {
        for (auto e : building_map) {
            Building* buliding = e.second;
            if (buliding->ocupation_area.intersects(area)) {
                return buliding;
            }
        }
        return nullptr;
    }

    int GetAssignableHouseId() {
        for (auto e : building_map) {
            Building* building = e.second;
            if (building->building_role == eBuildingRole::HOUSE && building->IsAssignable()) {
                return building->id;
            }
        }
        printf("INFO: [BuildingRepository] there is no assignable house.\n");
        return -1;
    }

    bool IsExistId(int id) {
        return building_map.find(id) != building_map.end();
    }

    ~BuildingRepository() {
        for (auto item : building_map) {
            delete(item.second);
        }
    }

    map<int, Building*>* GetBuildingMap() {
        return &building_map;
    }
};

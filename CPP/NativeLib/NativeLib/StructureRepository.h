#pragma once

#include "Structure.h"
#include "Base.h"
#include <map>

class StructureRepository {
private:
    map<int, Structure*> structure_map; // building_map[id] = building;
public:
    void AddStructure(Structure* structure) {
        if (IsExistId(structure->id)) {
            printf("[StructureRepository]ERROR: structure id is duplicated.\n");
        }
        else {
            structure_map[structure->id] = structure;
        }
    }
    void DeleteStructureById(int id) {
        if (IsExistId(id)) {
            Structure* structure = structure_map[id];

            for (auto block : structure->blocks) {
                block->Disappear();
            }

            delete(structure_map[id]);
            structure_map.erase(id);
        }
        else {
            printf("[StructureRepository]WARNING: trying to delete not exist structure.\n");
        }
    }
    Structure* GetStructureById(int id) {
        if (IsExistId(id)) {
            return structure_map[id];
        }
        else {
            printf("[StructureRepository]ERROR: trying to get not exist structure.\n");
        }
    }
    bool IsExistId(int id) {
        return structure_map.find(id) != structure_map.end();
    }
};
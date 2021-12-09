#pragma once

#include "Base.h"
#include "BlockTypeProperty.h"

enum class eStructureType {
    SINGLE_BED,
    DOUBLE_BED,
    BOX,
    COOKING_TABLE,
    POT,
    TABLE,
    COUNTER,
    CHAIR,
    TREE
};

class StructureData {
public:
    StructureData(eStructureType type);
    string name;
    int build_cost;
    int width;
    int height;
    vector< vector<eBlockType> > blocks;
    bool has_inventory = false;
    int inventory_size_x = -1;
    int inventory_size_y = -1;
};
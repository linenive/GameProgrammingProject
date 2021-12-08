#pragma once

#include "Base.h"
#include "BlockTypeProperty.h"
#include "BuildingRole.h"

#define ww eBlockType::WOOD_WALL
#define wd eBlockType::WOOD_DOOR
#define wf eBlockType::WOOD_FLOOR
#define ws eBlockType::SHOP_SIGN

enum class eBuildingType {
    SMALL_HOUSE,
    LARGE_HOUSE,
    NORMAL_SHOP,
};

class BuildingData {
public:
    BuildingData(eBuildingType type);
    string name;
    int build_cost;
    int width;
    int height;
    int slot_num;
    vector< vector<eBlockType> > blocks;
    eBuildingRole building_role;
};
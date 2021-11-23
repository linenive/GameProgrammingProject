#pragma once

#include "Base.h"
#include "BlockTypeProperty.h"

#define ww eBlockType::WOOD_WALL
#define wd eBlockType::WOOD_DOOR
#define wf eBlockType::WOOD_FLOOR

enum class eBuildingType {
    SMALL_HOUSE,
    LARGE_HOUSE
};

class BuildingData {
public:
    BuildingData(eBuildingType type);
    string name;
    int width;
    int height;
    int slot_num;
    vector< vector<eBlockType> > blocks;
};
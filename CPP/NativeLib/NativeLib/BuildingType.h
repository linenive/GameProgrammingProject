#pragma once

#include "Base.h"
#include "BlockType.h"

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

BuildingData::BuildingData(eBuildingType type) {
    switch (type)
    {
    case eBuildingType::SMALL_HOUSE:
        name = "small_house";
        width = 5;
        height = 5;
        slot_num = 2;
        blocks = {
            {ww, ww, ww, ww, ww},
            {ww, wf, wf, wf, ww},
            {ww, wf, wf, wf, ww},
            {ww, wf, wf, wf ,ww},
            {ww, ww, wd, ww, ww}
        };
        break;
    case eBuildingType::LARGE_HOUSE:
        name = "large_house";
        width = 7;
        height = 7;
        slot_num = 2;
        blocks = {
            {ww, ww, ww, ww, ww, ww, ww},
            {ww, wf, wf, wf, wf, wf, ww},
            {ww, wf, wf, wf, wf, wf, ww},
            {ww, wf, wf, wf, wf, wf, ww},
            {ww, wf, wf, wf, wf, wf, ww},
            {ww, wf, wf, wf, wf, wf, ww},
            {ww, ww, ww, wd, ww, ww, ww},
        };
        break;
    default:
        break;
    }
}
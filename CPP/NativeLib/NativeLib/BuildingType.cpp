#include "BuildingType.h"

BuildingData::BuildingData(eBuildingType type) {
    building_role = eBuildingRole::HOUSE;
    slot_num = 1;

    switch (type)
    {
    case eBuildingType::SMALL_HOUSE:
        name = "small_house";
        building_role = eBuildingRole::HOUSE;
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
        building_role = eBuildingRole::HOUSE;
        slot_num = 4;
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
    case eBuildingType::NORMAL_SHOP:
        name = "normal_shop";
        building_role = eBuildingRole::WORK_SPACE;
        slot_num = 3;
        blocks = {
            {ww, ww, ww, ww, ww, ww, ww, ww},
            {ww, wf, wf, wf, wf, wf, wf, ww},
            {ww, wf, wf, wf, wf, wf, wf, ww},
            {ww, wf, wf, wf, wf, wf, wf, ww},
            {ww, wf, wf, wf, wf, wf, wf, ww},
            {ww, wf, wf, wf, wf, wf, wf, ww},
            {ww, wf, wf, wf, wf, wf, wf, ww},
            {ww, ww, ww, wd, wd, ww, ww, ww},
        };
        break;
    default:
        break;
    }
    width = blocks[0].size();
    height = blocks.size();
}
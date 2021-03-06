#include "BuildingType.h"
#pragma execution_character_set("utf-8")

BuildingData::BuildingData(eBuildingType type) {
    building_role = eBuildingRole::HOUSE;
    slot_num = 1;
    build_cost = 0;

    switch (type)
    {
    case eBuildingType::SMALL_HOUSE:
        name = "작은 집";
        build_cost = 200000;
        building_role = eBuildingRole::HOUSE;
        slot_num = 1;
        blocks = {
            {ww, ww, ww, ww, ww},
            {ww, wf, wf, wf, ww},
            {ww, wf, wf, wf, ww},
            {ww, wf, wf, wf ,ww},
            {ww, ww, wd, ww, ww}
        };
        break;
    case eBuildingType::LARGE_HOUSE:
        name = "커다란 집";
        build_cost = 500000;
        building_role = eBuildingRole::HOUSE;
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
    case eBuildingType::THREE_ROOM_HOUSE:
        name = "쓰리룸 집";
        build_cost = 750000;
        building_role = eBuildingRole::HOUSE;
        slot_num = 3;
        blocks = {
            {ww, ww, ww, ww, ww, ww, ww, ww, ww},
            {ww, wf, wf, wf, ww, wf, wf, wf, ww},
            {wd, wf, wf, wf, wd, wf, wf, wf, ww},
            {ww, wf, wf, wf, ww, wf, wf, wf, ww},
            {ww, ww, wd, ww, ww, ww, ww, ww, ww},
            {ww, wf, wf, wf, wf, wf, wf, wf, ww},
            {ww, wf, wf, wf, wf, wf, wf, wf, ww},
            {ww, wf, wf, wf, wf, wf, wf, wf, ww},
            {ww, wf, wf, wf, wf, wf, wf, wf, ww},
            {ww, wf, wf, wf, wf, wf, wf, wf, ww},
            {ww, ww, ww, ww, ww, ww, ww, ww, ww},
        };
        break;
    case eBuildingType::NORMAL_SHOP:
        name = "상점";
        build_cost = 1000000;
        building_role = eBuildingRole::WORK_SPACE;
        slot_num = 4;
        blocks = {
            {ww, ww, ww, ww, ww, ww, ww, ww},
            {ww, wf, wf, wf, wf, wf, wf, ww},
            {ww, wf, wf, wf, wf, wf, wf, ww},
            {ww, wf, wf, wf, wf, wf, wf, ww},
            {ww, wf, wf, wf, wf, wf, wf, ww},
            {ww, wf, wf, wf, wf, wf, wf, ww},
            {ww, wf, wf, wf, wf, wf, wf, ww},
            {ww, ww, ws, wd, wd, ws, ww, ww},
        };
        break;
    case eBuildingType::TWO_ROOM_TWO_DOOR_SHOP:
        name = "투룸 상점1";
        build_cost = 1250000;
        building_role = eBuildingRole::WORK_SPACE;
        slot_num = 5;
        blocks = {
            {ww, ww, ww, ww, ww, ww, ww, ww},
            {ww, wf, wf, wf, wf, ww, wf, ww},
            {ww, wf, wf, wf, wf, ww, wf, ww},
            {ww, wf, wf, wf, wf, wd, wf, ww},
            {ww, wf, wf, wf, wf, ww, wf, ww},
            {ww, ww, wd, ww, ww, ww, wf, ww},
            {ww, wf, wf, wf, wf, wf, wf, ww},
            {ww, wf, wf, wf, wf, wf, wf, ww},
            {ww, ww, ws, wd, wd, ws, ww, ww},
        };
        break;
    case eBuildingType::TWO_ROOM_THREE_DOOR_SHOP:
        name = "투룸 상점2";
        build_cost = 1500000;
        building_role = eBuildingRole::WORK_SPACE;
        slot_num = 6;
        blocks = {
            {ww, ww, ww, ww, ww, ww, ww, ww, ww},
            {ww, wf, wf, wf, wf, ww, wf, wf, ww},
            {ws, wf, wf, wf, wf, ww, wf, wf, ww},
            {wd, wf, wf, wf, wf, wd, wf, wf, ww},
            {wd, wf, wf, wf, wf, wd, wf, wf, ww},
            {ws, wf, wf, wf, wf, ww, wf, wf, ww},
            {ww, wf, wf, wf, wf, ww, wf, wf, ww},
            {ww, ww, ww, ww, ww, ww, ww, ww, ww},
        };
        break;
    default:
        break;
    }
    width = blocks[0].size();
    height = blocks.size();
}
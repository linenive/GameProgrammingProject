#include "BuildingType.h"
#pragma execution_character_set("utf-8")

BuildingData::BuildingData(eBuildingType type) {
    building_role = eBuildingRole::HOUSE;
    slot_num = 1;
    build_cost = 0;

    switch (type)
    {
    case eBuildingType::SMALL_HOUSE:
        name = "���� ��";
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
        name = "Ŀ�ٶ� ��";
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
    case eBuildingType::NORMAL_SHOP:
        name = "����";
        build_cost = 1000000;
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
            {ww, ww, ws, wd, wd, ws, ww, ww},
        };
        break;
    default:
        break;
    }
    width = blocks[0].size();
    height = blocks.size();
}
#include "BuildingType.h"

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
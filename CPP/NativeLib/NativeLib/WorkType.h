#pragma once

#include "Base.h"
#include "StatField.h"

enum class eWorkType {
    COLLECT_WOOD,
    COLLECT_STONE,

    CREATE_ITEM,
    SELL_ITEM
};

class WorkType {
private:
    static map<eWorkType, string> work_type_name_dictionary;
public:
    static string NameOf(eWorkType type) {
        return work_type_name_dictionary[type];
    }
    static eStatFieldType ToStatFieldType(eWorkType type) {
        //To-do with csv file
        switch (type) {
        case eWorkType::COLLECT_WOOD:
            return eStatFieldType::LOGGING_WORK_SPEED;
            break;
        case eWorkType::COLLECT_STONE:
            return eStatFieldType::MINING_SPEED;
            break;
        case eWorkType::CREATE_ITEM:
            return eStatFieldType::ITEM_CREATE_SPEED;
            break;
        case eWorkType::SELL_ITEM:
            return eStatFieldType::SELL_ITEM_LEVEL;
            break;
        default:
            printf("WARNING [eStatFieldType::ToStatFieldType] Uncontrolled case.\n");
            return eStatFieldType::BASE_WORK_SPEED;
            break;
        }
    }
    static string ItemNameOf(eWorkType type) {
        //To-do with csv file
        switch (type) {
        case eWorkType::COLLECT_WOOD:
            return "wood";
            break;
        case eWorkType::COLLECT_STONE:
            return "stone";
            break;
        default:
            printf("WARNING [eStatFieldType::ToStatFieldType] Uncontrolled case.\n");
            return "Dummy";
            break;
        }
    }
    static void Init() {
        //To-do with csv file
        work_type_name_dictionary[eWorkType::COLLECT_WOOD] = "목재 수집";
        work_type_name_dictionary[eWorkType::COLLECT_STONE] = "돌 수집";

        work_type_name_dictionary[eWorkType::CREATE_ITEM] = "아이템 제작";
        work_type_name_dictionary[eWorkType::SELL_ITEM] = "손님 응대";
    }
};
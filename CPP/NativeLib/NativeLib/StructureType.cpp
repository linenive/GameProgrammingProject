#include "StructureType.h"

#define lb eBlockType::STRUCTURE_LOW_BLOCK
#define mb eBlockType::STRUCTURE_MID_BLOCK
#define hb eBlockType::STRUCTURE_HIGH_BLOCK

StructureData::StructureData(eStructureType type) {
    switch (type)
    {
    case eStructureType::SINGLE_BED:
        name = "single_bed";
        build_cost = 20000;
        blocks = {
            {mb},
            {mb},
        };
        break;
    case eStructureType::DOUBLE_BED:
        name = "double_bed";
        build_cost = 40000;
        blocks = {
            {mb, mb},
            {mb, mb},
        };
        break;
    case eStructureType::BOX:
        name = "box";
        build_cost = 3000;
        blocks = {
            {lb}
        };
        has_inventory = true;
        inventory_size_x = 3;
        inventory_size_y = 1;
        break;
    case eStructureType::COOKING_TABLE:
        name = "cooking_table";
        build_cost = 80000;
        blocks = {
            {mb, mb, mb}
        };
        has_inventory = true;
        inventory_size_x = 3;
        inventory_size_y = 2;
        break;
    case eStructureType::POT:
        name = "pot";
        build_cost = 3000;
        blocks = {
            {lb}
        };
        break;
    case eStructureType::TABLE:
        name = "table";
        build_cost = 10000;
        blocks = {
            {mb, mb}
        };
        has_inventory = true;
        inventory_size_x = 2;
        inventory_size_y = 2;
        break;
    case eStructureType::COUNTER:
        name = "counter";
        build_cost = 10000;
        blocks = {
            {mb}
        };
        has_inventory = true;
        inventory_size_x = 2;
        inventory_size_y = 1;
        break;
    case eStructureType::CHAIR:
        name = "chair";
        build_cost = 10000;
        blocks = {
            {lb}
        };
        break;
    case eStructureType::TREE:
        name = "tree";
        build_cost = 50000;
        blocks = {
            {mb}
        };
        break;
    default:
        break;
    }
    width = blocks[0].size();
    height = blocks.size();
}
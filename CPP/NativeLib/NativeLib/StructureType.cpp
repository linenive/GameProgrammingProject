#include "StructureType.h"

#define lb eBlockType::STRUCTURE_LOW_BLOCK
#define mb eBlockType::STRUCTURE_MID_BLOCK
#define hb eBlockType::STRUCTURE_HIGH_BLOCK

StructureData::StructureData(eStructureType type) {
    switch (type)
    {
    case eStructureType::SINGLE_BED:
        name = "single_bed";
        blocks = {
            {mb},
            {mb},
        };
        break;
    case eStructureType::DOUBLE_BED:
        name = "double_bed";
        blocks = {
            {mb, mb},
            {mb, mb},
        };
        break;
    case eStructureType::BOX:
        name = "box";
        blocks = {
            {lb}
        };
        break;
    case eStructureType::COOKING_TABLE:
        name = "cooking_table";
        blocks = {
            {mb, mb, mb}
        };
        break;
    case eStructureType::POT:
        name = "pot";
        blocks = {
            {lb}
        };
        break;
    case eStructureType::TABLE:
        name = "table";
        blocks = {
            {mb, mb}
        };
        break;
    case eStructureType::COUNTER:
        name = "counter";
        blocks = {
            {mb}
        };
        break;
    case eStructureType::CHAIR:
        name = "chair";
        blocks = {
            {lb}
        };
        break;
    default:
        break;
    }
    width = blocks[0].size();
    height = blocks.size();
}
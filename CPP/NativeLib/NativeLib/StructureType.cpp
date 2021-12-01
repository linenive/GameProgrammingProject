#include "StructureType.h"

#define sb eBlockType::STRUCTURE_BLOCK

StructureData::StructureData(eStructureType type) {
    switch (type)
    {
    case eStructureType::SINGLE_BED:
        name = "single_bed";
        blocks = {
            {sb},
            {sb},
        };
        break;
    case eStructureType::DOUBLE_BED:
        name = "double_bed";
        blocks = {
            {sb, sb},
            {sb, sb},
        };
        break;
    case eStructureType::BOX:
        name = "box";
        blocks = {
            {sb}
        };
    case eStructureType::COOKING_TABLE:
        name = "cooking_table";
        blocks = {
            {sb, sb, sb}
        };
    case eStructureType::POT:
        name = "pot";
        blocks = {
            {sb}
        };
    case eStructureType::TABLE:
        name = "table";
        blocks = {
            {sb}
        };
    case eStructureType::COUNTER:
        name = "counter";
        blocks = {
            {sb}
        };
    case eStructureType::CHAIR:
        name = "chair";
        blocks = {
            {sb}
        };
    default:
        width = blocks[0].size();
        height = blocks.size();
        break;
    }
}
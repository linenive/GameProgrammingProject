#include "StructureType.h"

#define wt eBlockType::WOOD_TABLE
#define wc eBlockType::WOOD_CHAIR

StructureData::StructureData(eStructureType type) {
    switch (type)
    {
    case eStructureType::WOOD_TABLE:
        name = "wood_table";
        blocks = {
            {wt, wt, wt},
            {wt, wt, wt},
        };
        break;
    case eStructureType::WOOD_CHAIR:
        name = "wood_chair";
        blocks = {
            {wc}
        };
        break;
    default:
        width = blocks[0].size();
        height = blocks.size();
        break;
    }
}
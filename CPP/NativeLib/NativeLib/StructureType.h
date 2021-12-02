#pragma once

#include "Base.h"
#include "BlockTypeProperty.h"

enum class eStructureType {
    SINGLE_BED,
    DOUBLE_BED,
    BOX,
    COOKING_TABLE,
    POT,
    TABLE,
    COUNTER,
    CHAIR
};

class StructureData {
public:
    StructureData(eStructureType type);
    string name;
    int width;
    int height;
    vector< vector<eBlockType> > blocks;
};
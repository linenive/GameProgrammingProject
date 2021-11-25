#pragma once

#include "Base.h"
#include "BlockTypeProperty.h"

enum class eStructureType {
    WOOD_TABLE,
    WOOD_CHAIR
};

class StructureData {
public:
    StructureData(eStructureType type);
    string name;
    int width;
    int height;
    vector< vector<eBlockType> > blocks;
};
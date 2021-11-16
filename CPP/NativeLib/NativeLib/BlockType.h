#pragma once

#include "Base.h"

enum class eBlockType {
    WOOD_WALL,
    WOOD_DOOR,
    WOOD_FLOOR
};

class BlockType {
public:
    static int LevelOf(eBlockType type);
    static string NameOf(eBlockType type);

    static int level[10];
    static string name[10];

    //TODO: init by external file
    static void Init() {
        level[static_cast<int>(eBlockType::WOOD_WALL)] = 1;
        name[static_cast<int>(eBlockType::WOOD_WALL)] = "wood_wall";

        level[static_cast<int>(eBlockType::WOOD_DOOR)] = 1;
        name[static_cast<int>(eBlockType::WOOD_DOOR)] = "wood_door";

        level[static_cast<int>(eBlockType::WOOD_FLOOR)] = 0;
        name[static_cast<int>(eBlockType::WOOD_FLOOR)] = "wood_floor";
    }
};

int BlockType::level[10];
string BlockType::name[10];

int BlockType::LevelOf(eBlockType type) {
    return BlockType::level[static_cast<int>(type)];
}

string BlockType::NameOf(eBlockType type) {
    return BlockType::name[static_cast<int>(type)];
}

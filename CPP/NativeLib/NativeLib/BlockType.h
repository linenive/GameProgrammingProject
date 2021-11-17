#pragma once

#include "Base.h"

enum class eBlockType {
    NONE,
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

    //To-do: init by external file
    static void Init() {
        level[static_cast<int>(eBlockType::WOOD_WALL)] = 1;
        name[static_cast<int>(eBlockType::WOOD_WALL)] = "wood_wall";

        level[static_cast<int>(eBlockType::WOOD_DOOR)] = 0;
        name[static_cast<int>(eBlockType::WOOD_DOOR)] = "wood_door";

        level[static_cast<int>(eBlockType::WOOD_FLOOR)] = 0;
        name[static_cast<int>(eBlockType::WOOD_FLOOR)] = "wood_floor";
    }
};
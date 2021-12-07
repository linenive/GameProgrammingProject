#pragma once

#include "Base.h"

enum class eBlockType {
    NONE,
    WOOD_WALL,
    WOOD_DOOR,
    WOOD_FLOOR,
    SHOP_SIGN,
    STRUCTURE_LOW_BLOCK,
    STRUCTURE_MID_BLOCK,
    STRUCTURE_HIGH_BLOCK
};

class BlockTypeProperty {
private:
    static bool is_initialized;

public:
    static int LevelOf(eBlockType type);
    static string NameOf(eBlockType type);
    static float PassSpeedOf(eBlockType type);

    static int level[10];
    static string name[10];
    static float pass_speed[10];

    //To-do: init by external file
    static void Init() {
        level[static_cast<int>(eBlockType::WOOD_WALL)] = 1;
        name[static_cast<int>(eBlockType::WOOD_WALL)] = "wood_wall";
        pass_speed[static_cast<int>(eBlockType::WOOD_WALL)] = 0.0;

        level[static_cast<int>(eBlockType::WOOD_DOOR)] = 0;
        name[static_cast<int>(eBlockType::WOOD_DOOR)] = "wood_door";
        pass_speed[static_cast<int>(eBlockType::WOOD_DOOR)] = 1.0;

        level[static_cast<int>(eBlockType::WOOD_FLOOR)] = 0;
        name[static_cast<int>(eBlockType::WOOD_FLOOR)] = "wood_floor";
        pass_speed[static_cast<int>(eBlockType::WOOD_FLOOR)] = 1.0;

        level[static_cast<int>(eBlockType::SHOP_SIGN)] = 1;
        name[static_cast<int>(eBlockType::SHOP_SIGN)] = "shop_sign";
        pass_speed[static_cast<int>(eBlockType::SHOP_SIGN)] = 0.0;

        level[static_cast<int>(eBlockType::STRUCTURE_LOW_BLOCK)] = 1;
        name[static_cast<int>(eBlockType::STRUCTURE_LOW_BLOCK)] = "low_block";
        pass_speed[static_cast<int>(eBlockType::STRUCTURE_LOW_BLOCK)] = 0.8;

        level[static_cast<int>(eBlockType::STRUCTURE_MID_BLOCK)] = 1;
        name[static_cast<int>(eBlockType::STRUCTURE_MID_BLOCK)] = "mid_block";
        pass_speed[static_cast<int>(eBlockType::STRUCTURE_MID_BLOCK)] = 0.4;

        level[static_cast<int>(eBlockType::STRUCTURE_HIGH_BLOCK)] = 1;
        name[static_cast<int>(eBlockType::STRUCTURE_HIGH_BLOCK)] = "high_block";
        pass_speed[static_cast<int>(eBlockType::STRUCTURE_HIGH_BLOCK)] = 0.0;
    }
};
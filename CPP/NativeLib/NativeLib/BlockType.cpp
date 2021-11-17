#include "BlockType.h"

int BlockType::level[10];
string BlockType::name[10];

int BlockType::LevelOf(eBlockType type) {
    return BlockType::level[static_cast<int>(type)];
}

string BlockType::NameOf(eBlockType type) {
    return BlockType::name[static_cast<int>(type)];
}
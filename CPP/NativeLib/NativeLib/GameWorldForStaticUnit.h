#pragma once

#include "Tile.h"
#include "BuildingRepository.h"

class GameWorldForStaticUnit {
public:
    virtual Tile* GetTileByPos(int pos_x, int pos_y) = 0;
    virtual Building* GetBuildingById(int id) = 0;
    virtual void AddBuilding(Building* building) = 0;
    virtual void DeleteBuildingFromWorld(int id) = 0;
};
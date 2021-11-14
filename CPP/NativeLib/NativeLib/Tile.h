#pragma once
#include "Surface.h"
#include "WorldObject.h"
#include "Block.h"

class Tile {
private:
	Block* layer[MAX_TILE_LAYER];
	Surface surface;

public:
	Tile(Surface _surface) :surface(_surface) {}
	WorldObject* GetTopWorldObject() {
		int i;
		for (i = MAX_TILE_LAYER - 1; i >= 0; i--) {
			if (layer[i] != nullptr) {
				return layer[i];
			}
		}
		return &surface;
	}

	float GetPassSpeed() {
		// To-do
	}

	Surface GetSurface() {
		return surface;
	}

	void SetSurfaceType(SurfaceType type) {
		surface.SetSurfaceType(type);
	}

	void SetBlock(Block* block, int layer_num) {
		layer[layer_num] = block;
	}

	bool IsEmptyLayer(int layer_num) {
		if (layer_num >= MAX_TILE_LAYER)
			return false;
		return layer[layer_num] == nullptr;
	}
};
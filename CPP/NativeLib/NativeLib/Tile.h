#pragma once
#include "Surface.h"
#include "WorldObject.h"

class Tile {
private:
	WorldObject* layer[MAX_TILE_LAYER];
	Surface surface;

public:
	Tile(Surface _surface):surface(_surface){}
	WorldObject* GetTopWorldObject() {
		int i;
		for (i = MAX_TILE_LAYER - 1; i >= 0 ; i--) {
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
};
#pragma once
#include "Surface.h"
#include "WorldObject.h"
#include "Block.h"

class Tile {
private:
	Block* layer[MAX_TILE_LAYER];
	Surface* surface;

	Transform2D CreateTransform2D(Vector2 position) {
		real_t rotation = real_t(.0);
		return Transform2D(rotation, position);
	}

	Vector2 CreateScale() {
		return Vector2(TILE_WIDTH, TILE_HEIGHT);
	}

public:
	Tile(SurfaceType _surfaceType, Vector2 position) {
		surface = new Surface(_surfaceType, CreateTransform2D(position), CreateScale());
		surface->SetPassSpeed(1.0); //To-do not hard coding
		for (int i = 0; i < MAX_TILE_LAYER; i++) {
			layer[i] = new Block("base_block", CreateTransform2D(position), CreateScale());
		}
	}

	~Tile() {
		delete(surface);
		for (int i = 0; i < MAX_TILE_LAYER; i++) {
			delete(layer[i]);
		}
	}

	WorldObject* GetTopWorldObject() {
		int i;
		for (i = MAX_TILE_LAYER - 1; i >= 0; i--) {
			if (layer[i]->is_exist) {
				return layer[i];
			}
		}
		return surface;
	}

	float GetPassSpeed() {
		float speed = 1.0;
		for (int i = 0; i < MAX_TILE_LAYER; i++) {
			speed *= layer[i]->GetPassSpeed();
		}
		speed *= surface->GetPassSpeed();
		return speed;
	}

	Surface* GetSurface() {
		return surface;
	}

	void SetSurfaceType(SurfaceType type) {
		surface->SetSurfaceType(type);
	}

	Block* GetBlock(int _layer_index) {
		return layer[_layer_index];
	}

	bool IsEmptyLayer(int layer_index) {
		if (layer_index >= MAX_TILE_LAYER)
			return false;
		return layer[layer_index]->is_exist == false;
	}
};
#pragma once
#include "Surface.h"
#include "WorldObject.h"
#include "Block.h"
#include "BlockType.h"

class Tile {
private:
	Block* layer[MAX_TILE_LAYER];
	Surface* surface;

	Transform2D CreateTransform2D(float x, float y) {
		real_t rotation = real_t(.0);
		Vector2 position = Vector2(real_t(x), real_t(y));
		return Transform2D(rotation, position);
	}

	Vector2 CreateScale() {
		return Vector2(TILE_WIDTH, TILE_HEIGHT);
	}

public:
	Tile(SurfaceType _surfaceType, float _pos_x, float _pos_y) {
		surface = new Surface(_surfaceType, CreateTransform2D(_pos_x, _pos_y), CreateScale());
		for (int i = 0; i < MAX_TILE_LAYER; i++) {
			layer[i] = new Block("base_block", CreateTransform2D(_pos_x, _pos_y), CreateScale());
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
		// To-do
		return 1.0;
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

	bool IsEmptyLayer(int layer_num) {
		if (layer_num >= MAX_TILE_LAYER)
			return false;
		return layer[layer_num]->is_exist == false;
	}
};
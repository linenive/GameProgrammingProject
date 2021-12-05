#pragma once
#include "WorldObject.h"

enum eTileType {
	SURFACE_NONE, SURFACE_EARTH, SURFACE_ROCK, SURFACE_RIVER, SURFACE_OCEAN
};

class SurfaceType {
private:
	string name;
public:
	SurfaceType(eTileType tile_type) {
		type = tile_type;
		// To-do: 엑셀 문서를 읽는것으로 바꾸기
		if (type == SURFACE_NONE)
			name = "empty";
		else if (type == SURFACE_EARTH)
			name = "earth";
		else if (type == SURFACE_ROCK)
			name = "rock";
		else if (type == SURFACE_RIVER)
			name = "river";
		else if (type == SURFACE_OCEAN)
			name = "ocean";
	}
	eTileType type;
	string GetName() { return name; }
};

class Surface : public WorldObject {

private:
	SurfaceType surface_type;
public:
	Surface(SurfaceType tile_type, Transform2D transform, Vector2 new_scale) : WorldObject(tile_type.GetName(),
		transform, new_scale), surface_type(tile_type) {
	}

	void SetSurfaceType(SurfaceType type) {
		surface_type = type;
		name = type.GetName();
	}

	SurfaceType GetSurfaceType() { return surface_type; }

	float GetPassSpeed() {
		if (surface_type.type == SURFACE_RIVER || surface_type.type == SURFACE_OCEAN) {
			return 0.0;
		}
		else return 1.0;
	}

	void SetPassSpeed(float _pass_speed) {
		pass_speed = _pass_speed;
	}
};

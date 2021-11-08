#pragma once
#include "GameRule.h"
#include "Common.h"

class Coordinates {
public:
	int x, y;

	Coordinates() {
		x = -1;
		y = -1;
	}

	Coordinates(int x_coord, int y_coord) {
		x = x_coord;
		y = y_coord;
	}
};

// To-do: 카메라 위치 반영하여 계산
Coordinates AbsolutePositionToCoordinates(Vector2 apsolute_position);

Vector2 CoordinatesToCenterVector(Coordinates coord);
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
	bool operator<(const Coordinates& other) const {
		return std::make_pair(x, y) < std::make_pair(other.x, other.y);
	}
	bool operator==(const Coordinates& other) const {
		if (x == other.x && y == other.y) {
			return true;
		}
		else {
			return false;
		}
	}
	bool operator!=(const Coordinates& other) const {
		if (x == other.x && y == other.y) {
			return false;
		}
		else {
			return true;
		}
	}
};

// To-do: 카메라 위치 반영하여 계산
Coordinates AbsolutePositionToCoordinates(Vector2 apsolute_position);
Coordinates AbsolutePositionToCoordinates(Transform2D absolute_position);

Vector2 CoordinatesToCenterVector(Coordinates coord);

Vector2 ClingToCloseCoordinate(Vector2 apsolute_position);
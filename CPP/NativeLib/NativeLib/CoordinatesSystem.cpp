#include "CoordinatesSystem.h"

Coordinates AbsolutePositionToCoordinates(Vector2 absolute_position) {
	int x = (absolute_position.x - MAP_START_POS_X) / TILE_WIDTH;
	int y = (absolute_position.y - MAP_START_POS_Y) / TILE_HEIGHT;
	// 이 라이브러리에서는 좌표가 타일맵을 벗어나는 지 신경쓰지 않는다.
	if (x < 0) x -= 1;
	if (y < 0) y -= 1;
	return Coordinates(x, y);
}

Coordinates AbsolutePositionToCoordinates(Transform2D absolute_position) {
	int x = (absolute_position.get_origin().x - MAP_START_POS_X) / TILE_WIDTH;
	int y = (absolute_position.get_origin().y - MAP_START_POS_Y) / TILE_HEIGHT;

	if (x < 0) x -= 1;
	if (y < 0) y -= 1;
	return Coordinates(x, y);
}

Vector2 CoordinatesToCenterVector(Coordinates coord) {
	float x = coord.x * TILE_WIDTH + TILE_WIDTH / 2;
	float y = coord.y * TILE_HEIGHT + TILE_HEIGHT / 2;

	return Vector2(x, y);
}

Vector2 ClingToCloseCoordinate(Vector2 apsolute_position){
	return CoordinatesToCenterVector(AbsolutePositionToCoordinates(apsolute_position));
}

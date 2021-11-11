#include "CoordinatesSystem.h"

Coordinates ApsolutePositionToCoordinates(Vector2 apsolute_position) {
	int x = (apsolute_position.x - MAP_START_POS_X) / TILE_WIDTH;
	int y = (apsolute_position.y - MAP_START_POS_Y) / TILE_HEIGHT;
	// 이 라이브러리에서는 좌표가 타일맵을 벗어나는 지 신경쓰지 않는다.
	if (x < 0) x -= 1;
	if (y < 0) y -= 1;
	// printf("VectorToCoordinates: %d %d\n", x, y);
	return Coordinates(x, y);
}


Vector2 CoordinatesToCenterVector(Coordinates coord){
	float x = coord.x * TILE_WIDTH + TILE_WIDTH / 2;
	float y = coord.y * TILE_HEIGHT + TILE_HEIGHT / 2;

	return Vector2(x, y);
}

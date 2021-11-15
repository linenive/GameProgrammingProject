#pragma once
#include "TileRepository.h"
#include "CoordinatesSystem.h"
#include <unordered_map>
#include <set>

using namespace std;
class CompareWithScore {
public:
	bool operator()(const pair<Coordinates, int>& lhs, const pair<Coordinates, int>& rhs) const {
		return lhs.second < rhs.second; //오름차순
	}
};

struct CoordinatesHash {
	size_t operator()(const Coordinates& coor) const {
		return hash<int>()(coor.x) ^ hash<int>()(coor.y);
	}
};
class PathFinder {

private:

	TileRepository* tile_map;

	int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	int dy[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };

	int weight_h = 10;
	int weight_g_straight = 10;
	int weight_g_diagonal = 14;

	int AstarH(Coordinates start_tile, Coordinates end_tile);

	bool DetectObstacle(Coordinates next_tile);
	int CalculateTileNumberByCoordinates(Coordinates coord);
public:
	vector<Vector2> PathFinding(godot::Vector2 start_pos, godot::Vector2 target_pos);
	void SetTileRepository(TileRepository* tile);
	vector<Vector2> GetPathListByCoor(vector<Coordinates> ans);
};


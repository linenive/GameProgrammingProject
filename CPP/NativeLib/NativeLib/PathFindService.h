#pragma once
#include "TileRepository.h"
#include "CoordinatesSystem.h"
#include <unordered_map>
#include <set>
#include <queue>

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
class PathFindService {

private:
	TileRepository* tile_map;

	int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	int dy[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };

	int weight_h = 100;
	int weight_g_straight = 100;
	int weight_g_diagonal = 141;

	int AstarH(Coordinates start_tile, Coordinates end_tile);

	Vector2 CalcObstacleVector(Coordinates current_tile);
	bool IsPassableTile(Coordinates next_tile);

public:
	PathFindService(TileRepository* tile){
		tile_map = tile;
	}
	queue<Vector2>* PathFinding(godot::Vector2 start_pos, godot::Vector2 target_pos);
	queue<Vector2>* GetPathListByCoor(vector<Coordinates> ans, Vector2 target_pos);
};


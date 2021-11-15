#pragma once
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

	set<pair<Coordinates, int>, CompareWithScore> open_list;
	set<Coordinates> closed_list;
	vector<Coordinates> ans;
	unordered_map<Coordinates, int, CoordinatesHash> score_f_list;
	TileRepository* tile_map;

	//std::unordered_map<Coordinates, int, std::hash<Coordinates>, std::equal_to<Coordinates>, std::allocator<std::pair<const Coordinates, int>>>

	int weight_h = 10;
	int weight_g_straight = 10;
	int weight_g_diagonal = 14;

	int AstarH(Coordinates start_tile, Coordinates end_tile);
	int AstarG(Coordinates now_tile, Coordinates next_tile, int weight);
	void AstarF(Coordinates now_tile, int score_f, int score_g);

	bool DetectObstacle(Coordinates next_tile);
	int CalculateTileNumberByCoordinates(Coordinates coord);
	//int GetTileWeight(int tile_id);
public:
	void AstarInit();
	vector<Coordinates> PathFinding(godot::Vector2 start_pos, godot::Vector2 target_pos);
	void SetTileRepository(TileRepository* tile);

};


#pragma once
#include "PathFinder.h"

int PathFinder::AstarH(Coordinates start_tile, Coordinates end_tile){
	int x = abs(end_tile.x - start_tile.x);
	int y = abs(end_tile.y - start_tile.y);

	return (x + y) * weight_h;
}

vector<Vector2> PathFinder::PathFinding(Vector2 start_pos, Vector2 target_pos) {

	int i, x, y;
	int now_score_h, now_score_g;
	Coordinates now_tile, next_tile;

	set<pair<Coordinates, int>, CompareWithScore> open_list;
	set<Coordinates> closed_list;

	unordered_map<Coordinates, int, CoordinatesHash> score_f_list;
	vector<Coordinates> ans;

	Coordinates start_tile = ApsolutePositionToCoordinates(start_pos);
	Coordinates end_tile = ApsolutePositionToCoordinates(target_pos);

	Godot::print("[PathFinder] End Tile: " + target_pos);// Vector2(end_tile.x, end_tile.y));
	open_list.insert(make_pair(start_tile, 0));
	ans.push_back(start_tile);

	while (ans.back() != end_tile)
	{
		now_tile = (*open_list.begin()).first;
		//Godot::print("[PathFinder] now tile: "+ Vector2(now_tile.x, now_tile.y) +", weight "+ Vector2(-1, (*open_list.begin()).second));
		closed_list.insert(now_tile);
		ans.push_back(now_tile);

		open_list.clear();

		for (i = 0; i < 8; i++) {

			x = now_tile.x + dx[i];
			y = now_tile.y + dy[i];
			next_tile.x = x;
			next_tile.y = y;

			if (x < 0 || y < 0 || x > MAX_TILE_NUMBER_X || y > MAX_TILE_NUMBER_Y) continue;

			auto it = closed_list.find(next_tile);
			if (it != closed_list.end()) continue;

			if (DetectObstacle(next_tile)) continue;

			now_score_h = AstarH(next_tile, end_tile);

			//AstarG
			if (dx[i] == 0 || dy[i] == 0) now_score_g = score_f_list[now_tile] + weight_g_straight;
			else now_score_g = score_f_list[now_tile] + weight_g_diagonal;

			//AstarF
			score_f_list.insert(unordered_map<Coordinates, int>::value_type(next_tile, (now_score_h + now_score_g)));

			open_list.insert(make_pair(next_tile, score_f_list[next_tile]));
		}
	}

	vector<Vector2> new_path = GetPathListByCoor(ans);

	Godot::print("[PathFinder] Change before last pos: " + new_path[new_path.size() - 1]);
	new_path[new_path.size() - 1] = target_pos;

	for (i = 0; i < new_path.size(); i++) {
		Godot::print("[PathFinder] PATH: " + new_path[i]);
	}
	return new_path;
}

void PathFinder::SetTileRepository(TileRepository* tile){
	tile_map = tile;

	//path finding 다시 해줘야 할수도 start, end를 매개변수로 받아서
}

bool PathFinder::DetectObstacle(Coordinates next_tile) {
	
	int tile_ind = CalculateTileNumberByCoordinates(next_tile);
	int tile_type = (tile_map->GetTile(tile_ind).GetTileType().type);
	return  tile_type > 1;
}

vector<Vector2> PathFinder::GetPathListByCoor(vector<Coordinates> ans) {

	std::vector<Coordinates>::iterator iter;
	vector<Vector2> ans_vector;
	for (iter = ans.begin(); iter != ans.end(); iter++) {
		ans_vector.push_back(CoordinatesToCenterVector((*iter)));
	}

	return ans_vector;
}

// 다른데서 받아와야 함
int PathFinder::CalculateTileNumberByCoordinates(Coordinates coord) {
	int tile_size_x = tile_map->GetTileSizeX();
	return coord.x + tile_size_x * coord.y;
}





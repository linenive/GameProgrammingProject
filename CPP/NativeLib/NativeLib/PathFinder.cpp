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
	Coordinates last_tile = start_tile;

	//Godot::print("[PathFinder] End Tile: " + target_pos);
	open_list.insert(make_pair(start_tile, 0));
	ans.push_back(start_tile);

	while (ans.back() != end_tile)
		//for(int j=0; j<10; j++)
	{
		now_tile = (*open_list.begin()).first;
		closed_list.insert(now_tile);
		ans.push_back(now_tile);

		//open_list.clear();

		for (i = 0; i < 8; i++) {

			x = now_tile.x + dx[i];
			y = now_tile.y + dy[i];
			next_tile.x = x;
			next_tile.y = y;

			if (x < 0 || y < 0 || x >= MAX_TILE_NUMBER_X || y >= MAX_TILE_NUMBER_Y) continue;

			//auto it = ;
			if (closed_list.find(next_tile) != closed_list.end()) continue;
			//if (closed_list.count(next_tile)) continue;
			//auto it = find(ans.begin(), ans.end(),next_tile);
			//if (it != ans.end()) continue;

			if (DetectObstacle(next_tile)) continue;

			now_score_h = AstarH(next_tile, end_tile);

			//AstarG
			if (score_f_list.find(now_tile) == score_f_list.end()) {
				Godot::print("[PathFinder] has not score f: " + Vector2(now_tile.x, now_tile.y));
				Godot::print("[PathFinder] has not score f: " + Vector2(now_tile.x, now_tile.y));
			}

			if (dx[i] == 0 || dy[i] == 0) now_score_g = score_f_list[now_tile] + weight_g_straight;
			else now_score_g = score_f_list[now_tile] + weight_g_diagonal;

			//AstarF
			score_f_list.insert(unordered_map<Coordinates, int>::value_type(next_tile, (now_score_h + now_score_g)));

			Godot::print("[PathFinder] ADD OPEN LIST: " + Vector2(i, score_f_list[next_tile]));
			open_list.insert(make_pair(next_tile, score_f_list[next_tile]));
		}
	}
	vector<Vector2> new_path = GetPathListByCoor(ans);

	if (new_path.size() > 0) {
		new_path[new_path.size() - 1] = target_pos;
	}

	Godot::print("[PathFinder] End PathFinder: ");
	return new_path;
}
bool PathFinder::DetectObstacle(Coordinates next_tile) {
	
	int tile_ind = CalculateTileNumberByCoordinates(next_tile);
	int tile_type = (tile_map->GetTile(tile_ind).GetTileType().type);
	return  tile_type > 1;
}

void PathFinder::SetTileRepository(TileRepository* tile) {
	tile_map = tile;
	//path finding 다시 해줘야 할수도 start, end를 매개변수로 받아서
}

vector<Vector2> PathFinder::GetPathListByCoor(vector<Coordinates> ans) {

	std::vector<Coordinates>::iterator iter;
	vector<Vector2> ans_vector;
	for (iter = ans.begin()+1; iter != ans.end(); iter++) {
		ans_vector.push_back(CoordinatesToCenterVector((*iter)));
	}
	return ans_vector;
}

// 다른데서 받아와야 함
int PathFinder::CalculateTileNumberByCoordinates(Coordinates coord) {
	int tile_size_x = tile_map->GetTileSizeX();
	return coord.x + tile_size_x * coord.y;
}





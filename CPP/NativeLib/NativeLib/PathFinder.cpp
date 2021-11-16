#pragma once
#include "PathFinder.h"

int PathFinder::AstarH(Coordinates start_tile, Coordinates end_tile){
	int x = abs(end_tile.x - start_tile.x);
	int y = abs(end_tile.y - start_tile.y);

	return (x + y) * weight_h;
}

vector<Vector2> PathFinder::PathFinding(Vector2 start_pos, Vector2 target_pos) {

	int i, x, y;
	int now_score_h, now_score_g, now_score_f;
	Coordinates now_tile, next_tile;

	set<pair<Coordinates, int>, CompareWithScore> open_list;
	unordered_map<Coordinates, Coordinates, CoordinatesHash> open_parent_list;
	unordered_map<Coordinates, Coordinates, CoordinatesHash> closed_parent_list;

	unordered_map<Coordinates, int, CoordinatesHash> score_f_list;
	vector<Coordinates> ans;

	Coordinates start_tile = AbsolutePositionToCoordinates(start_pos);
	Coordinates end_tile = AbsolutePositionToCoordinates(target_pos);

	Godot::print("[PathFinder] Start Tile : "+ Vector2(start_tile.x, start_tile.y) +" End Tile : " + Vector2(end_tile.x, end_tile.y));
	open_list.insert(make_pair(start_tile, 0));
	open_parent_list[start_tile] = start_tile;
	score_f_list[start_tile] = 0;

	now_tile = start_tile;

	while (now_tile != end_tile && open_list.size()>0)
	{
		now_tile = (*open_list.begin()).first;
		closed_parent_list[now_tile] = open_parent_list[now_tile];

		//Godot::print("[PathFinder] ADD CLOSE Tile : " + Vector2(now_tile.x, now_tile.y) + " Parent Tile : " + Vector2(closed_parent_list[now_tile].x, closed_parent_list[now_tile].y)
		//+ " score : "+Vector2((*open_list.begin()).second,0));

		open_list.erase(open_list.begin());

		for (i = 0; i < 8; i++) {

			x = now_tile.x + dx[i];
			y = now_tile.y + dy[i];
			next_tile.x = x;
			next_tile.y = y;

			if (x < 0 || y < 0 || x >= MAX_TILE_NUMBER_X || y >= MAX_TILE_NUMBER_Y) continue;

			if (closed_parent_list.find(next_tile) != closed_parent_list.end()) continue;

			if (DetectObstacle(next_tile))
			{
				continue;
			}

			now_score_h = AstarH(next_tile, end_tile);

			//AstarG
			if (score_f_list.find(now_tile) == score_f_list.end()) {
				Godot::print("[PathFinder] has not score f: " + Vector2(now_tile.x, now_tile.y));
			}

			if (dx[i] == 0 || dy[i] == 0) now_score_g = score_f_list[now_tile] + weight_g_straight;
			else now_score_g = score_f_list[now_tile] + weight_g_diagonal;

			//AstarF
			now_score_f = (now_score_h + now_score_g);

			//has key next_tile
			if (open_parent_list.find(next_tile) != open_parent_list.end()) {

				//new key is larger score
				if (score_f_list[next_tile] < now_score_f) continue;
			}

			score_f_list.insert(unordered_map<Coordinates, int>::value_type(next_tile, now_score_f));
			open_list.insert(make_pair(next_tile, now_score_f));
			open_parent_list[next_tile] = now_tile;
		}
	}

	Coordinates parent_tile;
	now_tile = end_tile;

	//back tracking
	String path= Vector2(now_tile.x, now_tile.y);
	for (i=0; i<closed_parent_list.size(); i++)
	{
		parent_tile = closed_parent_list[now_tile];
		if (parent_tile == start_tile) break;	
		if (parent_tile.x < 0) break;
		//Godot::print("[PathFinder] Push new path: " + Vector2(now_tile.x, now_tile.y)  + " from " + Vector2(parent_tile.x, parent_tile.y));
		now_tile = parent_tile;
		ans.insert(ans.begin(), parent_tile);

		path += " -> "+Vector2(parent_tile.x, parent_tile.y);
	}

	Godot::print("[PathFinder] GET Path: " + path);

	ans.push_back(end_tile);

	vector<Vector2> new_path = GetPathListByCoor(ans);

	if (new_path.size() > 0) {
		new_path[new_path.size() - 1] = target_pos;
	}

	return new_path;
}
bool PathFinder::DetectObstacle(Coordinates next_tile) {
	
	int tile_ind = CalculateTileNumberByCoordinates(next_tile);
	int tile_type = (int)(tile_map->GetTile(tile_ind).GetTileType().type);
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

// After fix -> get from another class
int PathFinder::CalculateTileNumberByCoordinates(Coordinates coord) {
	int tile_size_x = tile_map->GetTileSizeX();
	return coord.x + tile_size_x * coord.y;
}





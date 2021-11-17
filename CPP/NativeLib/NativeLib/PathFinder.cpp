#pragma once
#include "PathFinder.h"

int PathFinder::AstarH(Coordinates start_tile, Coordinates end_tile){
	int x = abs(end_tile.x - start_tile.x);
	int y = abs(end_tile.y - start_tile.y);

	return (x + y) * weight_h;
}

vector<Vector2> PathFinder::PathFinding(Vector2 start_pos, Vector2 target_pos) {

	int i, x, y;
	int current_score_h, current_score_g, current_score_f;
	Coordinates current_tile, next_tile;

	set<pair<Coordinates, int>, CompareWithScore> open_list;
	unordered_map<Coordinates, Coordinates, CoordinatesHash> open_parent_list;
	unordered_map<Coordinates, Coordinates, CoordinatesHash> closed_parent_list;

	unordered_map<Coordinates, Vector2, CoordinatesHash> obstacle_vector;

	unordered_map<Coordinates, int, CoordinatesHash> score_f_list;
	vector<Coordinates> ans;

	Coordinates start_tile = AbsolutePositionToCoordinates(start_pos);
	Coordinates end_tile = AbsolutePositionToCoordinates(target_pos);

	Godot::print("[PathFinder] Start Pos : "+ start_pos +" End Pos : " + target_pos);
	Godot::print("[PathFinder] Start Tile : "+ Vector2(start_tile.x, start_tile.y) +" End Tile : " + Vector2(end_tile.x, end_tile.y));
	open_list.insert(make_pair(start_tile, 0));
	open_parent_list[start_tile] = start_tile;
	score_f_list[start_tile] = 0;

	current_tile = start_tile;

	int loopcount = 0;
	while (current_tile != end_tile && open_list.size()>0)
	{
		if (loopcount > 200) break;
		loopcount++;
		current_tile = (*open_list.begin()).first;
		closed_parent_list[current_tile] = open_parent_list[current_tile];

		//Godot::print("[PathFinder] ADD CLOSE Tile : " + Vector2(current_tile.x, current_tile.y) + " Parent Tile : " + Vector2(closed_parent_list[current_tile].x, closed_parent_list[current_tile].y)
		//+ " score : "+Vector2((*open_list.begin()).second,0));

		open_list.erase(open_list.begin());

		for (i = 0; i < 8; i++) {

			x = current_tile.x + dx[i];
			y = current_tile.y + dy[i];
			next_tile.x = x;
			next_tile.y = y;

			if (x < 0 || y < 0 || x >= MAX_TILE_NUMBER_X || y >= MAX_TILE_NUMBER_Y) continue;

			if (closed_parent_list.find(next_tile) != closed_parent_list.end()) continue;

			if (DetectObstacle(next_tile)) continue;
			current_score_h = AstarH(next_tile, end_tile);

			//AstarG
			if (score_f_list.find(current_tile) == score_f_list.end()) {
				Godot::print("[PathFinder] has not score f: " + Vector2(current_tile.x, current_tile.y));
			}

			if (dx[i] == 0 || dy[i] == 0) current_score_g = score_f_list[current_tile] + weight_g_straight;
			else current_score_g = score_f_list[current_tile] + weight_g_diagonal;

			//AstarF
			current_score_f = (current_score_h + current_score_g);

			//has key next_tile
			if (open_parent_list.find(next_tile) != open_parent_list.end()) {
				//new key is larger score
				if (score_f_list[next_tile] < current_score_f) continue;
			}

			score_f_list.insert(unordered_map<Coordinates, int>::value_type(next_tile, current_score_f));
			open_list.insert(make_pair(next_tile, current_score_f));
			open_parent_list[next_tile] = current_tile;
		}
	}

	Coordinates parent_tile;
	current_tile = end_tile;

	//back tracking
	String path= Vector2(current_tile.x, current_tile.y);
	for (i=0; i<closed_parent_list.size(); i++)
	{
		parent_tile = closed_parent_list[current_tile];
		if (parent_tile == start_tile) break;	
		if (parent_tile.x < 0) break;
		//Godot::print("[PathFinder] Push new path: " + Vector2(current_tile.x, current_tile.y)  + " from " + Vector2(parent_tile.x, parent_tile.y));
		current_tile = parent_tile;
		ans.insert(ans.begin(), parent_tile);

		path += " -> "+Vector2(parent_tile.x, parent_tile.y);
	}

	Godot::print("[PathFinder] GET Path: " + path);
	Godot::print("[PathFinder] loop count: " + Vector2(0,loopcount));

	ans.push_back(end_tile);

	vector<Vector2> new_path = GetPathListByCoor(ans);

	if (new_path.size() > 0) {
		new_path[new_path.size() - 1] = target_pos;
	}

	return new_path;
}
bool PathFinder::DetectObstacle(Coordinates next_tile) {
	int tile_id = CalculateTileNumberByCoordinates(next_tile);
	int tile_type = (int)(tile_map->GetTile(tile_id)->GetSurface()->GetSurfaceType().type);
	return  tile_type > 1 && tile_map->GetTile(tile_id)->IsEmptyLayer(1);
}

void PathFinder::SetTileRepository(TileRepository* tile) {
	tile_map = tile;
}

Vector2 PathFinder::CalcObstacleVector(Coordinates current_tile) {
	int x, y;

	int dx[4] = { -1, 1, 0, 0};
	int dy[4] = { 0, 0, -1, 1};
	Vector2 obs_vec= Vector2(0,0);

	for (int i = 0; i < 4; i++) {
		x = current_tile.x + dx[i];
		y = current_tile.y + dy[i];

		if (x < 0 || y < 0 || x >= MAX_TILE_NUMBER_X || y >= MAX_TILE_NUMBER_Y) continue;
		if (DetectObstacle(Coordinates(x, y))) {
			obs_vec.x += dx[i];
			obs_vec.y += dy[i];
		}
	}

	obs_vec = -obs_vec.normalized();
	obs_vec = Vector2(obs_vec.x * TILE_WIDTH, obs_vec.y * TILE_HEIGHT);
	return obs_vec;
}

vector<Vector2> PathFinder::GetPathListByCoor(vector<Coordinates> ans) {

	std::vector<Coordinates>::iterator iter;
	vector<Vector2> ans_vector;
	for (iter = ans.begin()+1; iter != ans.end(); iter++) {
		ans_vector.push_back(CoordinatesToCenterVector((*iter)) + CalcObstacleVector((*iter)));
	}
	return ans_vector;
}

// After fix -> get from another class
int PathFinder::CalculateTileNumberByCoordinates(Coordinates coord) {
	int tile_size_x = tile_map->GetTileSizeX();
	return coord.x + tile_size_x * coord.y;
}





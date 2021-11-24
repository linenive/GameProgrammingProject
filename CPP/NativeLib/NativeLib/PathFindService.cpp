#pragma once
#include "PathFindService.h"
#include <math.h>

int PathFindService::AstarH(Coordinates start_tile, Coordinates end_tile){
	int x = abs(end_tile.x - start_tile.x);
	int y = abs(end_tile.y - start_tile.y);

	return sqrt(x*x + y*y) * weight_h;
}

queue<Vector2>* PathFindService::PathFinding(Vector2 start_pos, Vector2 target_pos) {

	int i, x, y;
	int current_score_h, current_score_g, current_score_f;
	Coordinates current_tile, next_tile;

	set<pair<Coordinates, int>, CompareWithScore> open_list;
	unordered_map<Coordinates, Coordinates, CoordinatesHash> open_parent_list;
	unordered_map<Coordinates, Coordinates, CoordinatesHash> closed_parent_list;

	unordered_map<Coordinates, Vector2, CoordinatesHash> obstacle_vector;

	unordered_map<Coordinates, int, CoordinatesHash> score_f_list;
	unordered_map<Coordinates, int, CoordinatesHash> moved_distance_list;
	vector<Coordinates> ans;

	Coordinates start_tile = AbsolutePositionToCoordinates(start_pos);
	Coordinates end_tile = AbsolutePositionToCoordinates(target_pos);

	Godot::print("[PathFinder] Start Pos : "+ start_pos +" End Pos : " + target_pos);
	Godot::print("[PathFinder] Start Tile : "+ Vector2(start_tile.x, start_tile.y) +" End Tile : " + Vector2(end_tile.x, end_tile.y));
	open_list.insert(make_pair(start_tile, 0));
	open_parent_list[start_tile] = start_tile;
	score_f_list[start_tile] = 0;
	moved_distance_list[start_tile] = 0;

	current_tile = start_tile;

	while (current_tile != end_tile && open_list.size()>0)
	{
		current_tile = (*open_list.begin()).first;
		open_list.erase(open_list.begin());
		if (closed_parent_list.find(current_tile) != closed_parent_list.end()) continue;

		closed_parent_list[current_tile] = open_parent_list[current_tile];

		//Godot::print("[PathFinder] ADD CLOSE Tile : " + Vector2(current_tile.x, current_tile.y) + " Parent Tile : " + Vector2(closed_parent_list[current_tile].x, closed_parent_list[current_tile].y)
		//+ " score : "+Vector2((*open_list.begin()).second,0));



		for (i = 0; i < 8; i++) {

			x = current_tile.x + dx[i];
			y = current_tile.y + dy[i];
			next_tile.x = x;
			next_tile.y = y;

			if (x < 0 || y < 0 || x >= DEFAULT_TILE_NUMBER_X || y >= DEFAULT_TILE_NUMBER_Y) continue;

			if (closed_parent_list.find(next_tile) != closed_parent_list.end()) continue;

			if (!IsPassableTile(next_tile))
			{
				continue;
			}

			current_score_h = AstarH(next_tile, end_tile);

			//AstarG
			if (score_f_list.find(current_tile) == score_f_list.end()) {
				Godot::print("[PathFinder] has not score f: " + Vector2(current_tile.x, current_tile.y));
			}

			if (dx[i] == 0 || dy[i] == 0) current_score_g = weight_g_straight;
			else current_score_g = weight_g_diagonal;

			//AstarF
			current_score_f = (current_score_h + current_score_g + moved_distance_list[current_tile]);

			//has key next_tile
			if (open_parent_list.find(next_tile) != open_parent_list.end()) {

				//new key is larger score
				if (score_f_list[next_tile] < current_score_f) continue;
			}

			score_f_list.insert(unordered_map<Coordinates, int>::value_type(next_tile, current_score_f));
			open_list.insert(make_pair(next_tile, current_score_f));
			open_parent_list[next_tile] = current_tile;
			moved_distance_list[next_tile] = moved_distance_list[current_tile] + current_score_g;
		}
	}

	Coordinates parent_tile;
	current_tile = end_tile;

	//back tracking
	String path= Vector2(current_tile.x, current_tile.y);
	printf("size: %d\n", closed_parent_list.size());
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

	//Godot::print("[PathFinder] GET Path: " + path);

	ans.push_back(end_tile);

	return GetPathListByCoor(ans, target_pos);
}
bool PathFindService::IsPassableTile(Coordinates next_tile) {
	return tile_map->IsPassableTile(next_tile.x, next_tile.y);
}

Vector2 PathFindService::CalcObstacleVector(Coordinates current_tile) {
	int x, y;

	int dx[4] = { -1, 1, 0, 0};
	int dy[4] = { 0, 0, -1, 1};
	Vector2 obs_vec= Vector2(0,0);

	for (int i = 0; i < 4; i++) {
		x = current_tile.x + dx[i];
		y = current_tile.y + dy[i];

		if (x < 0 || y < 0 || x >= DEFAULT_TILE_NUMBER_X || y >= DEFAULT_TILE_NUMBER_Y) continue;
		if (!IsPassableTile(Coordinates(x, y))) {
			obs_vec.x += dx[i];
			obs_vec.y += dy[i];
		}
	}

	obs_vec = -obs_vec.normalized();
	obs_vec = Vector2(obs_vec.x * TILE_WIDTH, obs_vec.y * TILE_HEIGHT);
	return obs_vec;
}

queue<Vector2>* PathFindService::GetPathListByCoor(vector<Coordinates> ans, Vector2 target_pos) {

	std::vector<Coordinates>::iterator iter;
	queue<Vector2>* ans_vector = new queue<Vector2>;
	for (iter = ans.begin()+1; iter != ans.end(); iter++) {
		ans_vector->push(CoordinatesToCenterVector((*iter)) + CalcObstacleVector((*iter)));
	}
	if (ans_vector->size() > 0) {
		// 확인하기
		ans_vector->push(target_pos);
	}
	return ans_vector;
}



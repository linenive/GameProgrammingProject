#pragma once
//#include "GodotScenePath.h"
#include "WorldManager.h"
#include "PathFinder.h"

WorldManager worldManager;
void PathFinder::AstarInit(){
	open_list.clear();
	ans.clear();
	score_f_list.clear();

	weight_h = 11;
}

int PathFinder::AstarH(Coordinates start_tile, Coordinates end_tile){
	int x = abs(end_tile.x - start_tile.x);
	int y = abs(end_tile.y - start_tile.y);

	//score_h.insert(hash_map<Coordinates, int>::value_type(start_tile, (x + y) * weightH));
	return (x + y) * weight_h;
}

int PathFinder::AstarG(Coordinates now_tile, Coordinates next_tile, int weight){
	//scoreG.insert(hash_map<Coordinates, int>::value_type(next_tile, scoreF[now_tile] + weight));
	return score_f_list[now_tile] + weight;
}

void PathFinder::AstarF(Coordinates next_tile, int score_f, int score_g){
	score_f_list.insert(unordered_map<Coordinates, int>::value_type(next_tile, score_f + score_g));
}

vector<Coordinates> PathFinder::PathFinding(Vector2 start_pos, Vector2 target_pos){

	int i, x, y;
	int now_score_h, now_score_g;
	Coordinates now_tile, next_tile;

	int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	int dy[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };

	Godot::print("[PathFinder] >>>> Start pos : " + start_pos);
	AstarInit();

	Coordinates start_tile = GetCoordinatesByVector(start_pos);
	Coordinates end_tile = GetCoordinatesByVector(target_pos);

	Godot::print("[PathFinder] Set Coordinates: (%d, %d) . (%d, %d)" ,(start_tile.x, start_tile,y, end_tile.x, end_tile.y));
	open_list.insert(make_pair(start_tile, 0));
	ans.push_back(start_tile);

	while (ans.back() != end_tile) {

		now_tile = (*open_list.begin()).first;
		ans.push_back(now_tile);

		for (i = 0; i < 8; i++) {

			x = now_tile.x + dx[i];
			y = now_tile.y + dy[i];
			next_tile.x = x;
			next_tile.y = y;

			if (x < 0 || y < 0 || x < MAX_TILE_NUMBER_X || y < MAX_TILE_NUMBER_Y) continue;
			if (DetectObstacle(next_tile))
			{
				Godot::print("[PathFinder] Obstacle Detect : ( %d, %d )" + (next_tile.x, next_tile.y));
				continue; // 장애물에 대해선 검사를 하지 않는다.
			}

			now_score_h = AstarH(next_tile, end_tile);

			if (dx[i] == 0 || dy[i] == 0) now_score_g = AstarG(now_tile, next_tile, weight_g_straight);
			else now_score_g = AstarG(now_tile, next_tile, weight_g_diagonal);

			AstarF(next_tile, now_score_h, now_score_g);

			open_list.insert(make_pair(next_tile, score_f_list[next_tile]));
		}
	}
	String print_string;

	for (int i = 0; i < ans.size(); i++) {
		print_string += "(" + ans[i].x;
		print_string += "," + ans[i].y;
		print_string += ") => ";
	}
	Godot::print("[PathFinder] Get Path : "+print_string);
	return ans;
}

bool PathFinder::DetectObstacle(Coordinates next_tile) {
	return worldManager.GetTileType(worldManager.CalculateTileNumberByCoordinates(next_tile)) > 1;
}
void PathFinder::SetWorldManager(){
	
	Godot::print("[PathFinder] Get WorldManager Test Called ");
	Node* node;
	node->godot::Node::get_node(NodePath("/root/Main/WorldManager"));
	ERR_FAIL_COND(node == nullptr);
	worldManager = *(node->cast_to<WorldManager>(node));
	//ERR_FAIL_COND(worldManager == nullptr);
	Godot::print("[PathFinder] Get WorldManager Test: " +worldManager.GetWorldSize());
}

Coordinates PathFinder::GetCoordinatesByVector(Vector2 pos) {
	int now_tile_id = worldManager.GetTileIdByVector2(pos);
	Godot::print("[PathFinder] Get Coordinate : " + pos + " : "+now_tile_id);
	return Coordinates(now_tile_id / MAX_TILE_NUMBER_X, now_tile_id % MAX_TILE_NUMBER_X);
}



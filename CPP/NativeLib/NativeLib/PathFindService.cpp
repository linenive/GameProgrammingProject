#pragma once
#include "PathFindService.h"
#include <math.h>

typedef tuple<int, int, Coordinates> P;

int PathFindService::AstarH(Coordinates start_tile, Coordinates end_tile) {
	int x = abs(end_tile.x - start_tile.x);
	int y = abs(end_tile.y - start_tile.y);

	return sqrt(x * x + y * y) * weight_h;
}

queue<Vector2>* PathFindService::PathFinding(Vector2 start_pos, Vector2 target_pos) {
	Coordinates start_tile = AbsolutePositionToCoordinates(start_pos);
	Coordinates end_tile = AbsolutePositionToCoordinates(target_pos);
	//Godot::print("[PathFinder] Start Pos : " + start_pos + " End Pos : " + target_pos);
	//Godot::print("[PathFinder] Start Tile : " + Vector2(start_tile.x, start_tile.y) + " End Tile : " + Vector2(end_tile.x, end_tile.y));

	priority_queue<P, vector<P>, greater<P> > pq; //score, distance, coordintes

	unordered_map<Coordinates, int, CoordinatesHash> min_score_map;
	unordered_map<Coordinates, Coordinates, CoordinatesHash> parent_map;

	int start_score = AstarH(start_tile, end_tile);
	min_score_map[start_tile] = start_score;

	pq.push({ start_score, 0, start_tile });
	Coordinates cur_tile;

	while (!pq.empty()) {
		int cur_score, cur_distance;
		tie(cur_score, cur_distance, cur_tile) = pq.top();
		pq.pop();

		if (cur_tile == end_tile)
			break;

		if (min_score_map[cur_tile] != 0 && min_score_map[cur_tile] < cur_score) //already visited
		{
			continue;
		}

		for (int i = 0; i < 8; i++) {
			Coordinates next_tile = Coordinates(cur_tile.x + dx[i], cur_tile.y + dy[i]);

			if (next_tile.x < 0 || next_tile.y < 0 || next_tile.x >= DEFAULT_TILE_NUMBER_X || next_tile.y >= DEFAULT_TILE_NUMBER_Y)
				continue;

			if (!IsPassableTile(next_tile))
				continue;

			int next_distance = cur_distance;
			float tile_pass_speed = GetTilePassSpeed(next_tile);
			if (dx[i] == 0 || dy[i] == 0)
				next_distance += weight_g_straight / tile_pass_speed;
			else
				next_distance += weight_g_diagonal / tile_pass_speed;

			int next_score = next_distance + AstarH(next_tile, end_tile);
			if (min_score_map[next_tile] == 0 || min_score_map[next_tile] > next_score) {
				min_score_map[next_tile] = next_score;
				pq.push({ next_score, next_distance, next_tile });
				parent_map[next_tile] = cur_tile;
			}
		}
	}
	vector<Coordinates> ans;

	while (cur_tile != start_tile) {
		ans.push_back(cur_tile);
		cur_tile = parent_map[cur_tile];
	}

	queue<Vector2>* ans_queue = new queue<Vector2>;
	while (!ans.empty()) {
		ans_queue->push(CoordinatesToCenterVector(ans.back())); // + CalcObstacleVector(ans.back()));
		ans.pop_back();
	}
	return ans_queue;
}

bool PathFindService::IsPassableTile(Coordinates next_tile) {
	return tile_service->IsPassableTile(next_tile);
}

float PathFindService::GetTilePassSpeed(Coordinates next_tile) {
	return tile_service->GetTilePassSpeed(next_tile);
}

Vector2 PathFindService::CalcObstacleVector(Coordinates current_tile) {
	int x, y;

	int dx[4] = { -1, 1, 0, 0 };
	int dy[4] = { 0, 0, -1, 1 };
	Vector2 obs_vec = Vector2(0, 0);

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

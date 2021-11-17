#pragma once
#include "TaskForIdleMove.h"
#include <random>
#include <ctime>


void TaskForIdleMove::ArriveTaskTarget() {

	Godot::print("[TaskForIdleMove] ARRIVE TASK: " + current_position);
	//Wait();
}

void TaskForIdleMove::SetIdleMove(){
	Godot::print("[TaskForIdleMove] SET IDLE MOVE: "+current_position);

	//while (current_moving == false) {
		Godot::print("[TaskForIdleMove] FIND PATH ");
		SetPathList(current_position, GetNewTarget());
	//}
}

Vector2 TaskForIdleMove::GetNewTarget(){
	Vector2 random_position = current_position + Vector2(rand() % 100 + 20, rand() % 100 + 20);
	Godot::print("[TaskForIdleMove] new random target: " + random_position);
	return  random_position;
}

void TaskForIdleMove::Wait(){
	//this_thread::sleep_for(chrono::seconds(2));
	time_t start, now;
	float wait_time = 3;
	start = time(NULL);
	for (; now - start > wait_time;) {
		now = time(NULL);
	}

	SetIdleMove();
}

void TaskForIdleMove::CreateTimer(float wait_time) {
}

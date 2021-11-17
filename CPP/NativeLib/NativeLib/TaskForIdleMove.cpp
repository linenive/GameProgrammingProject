#pragma once
#include "TaskForIdleMove.h"
#include <random>
#include <time.h>


void TaskForIdleMove::ArriveTaskTarget() {

	Godot::print("[TaskForIdleMove] ARRIVE TASK: " + current_position);
	Wait();
}

void TaskForIdleMove::SetIdleMove(){
	Godot::print("[TaskForIdleMove] SET IDLE MOVE: "+current_position);

	//while (current_moving == false) {
		Godot::print("[TaskForIdleMove] FIND PATH ");
		SetPathList(current_position, GetNewTarget());
	//}
}

Vector2 TaskForIdleMove::GetNewTarget(){
	Vector2 random_position = current_position + Vector2(rand() % 100 + 10, rand() % 100 + 10);
	Godot::print("[TaskForIdleMove] new random target: " + random_position);
	return  random_position;
}

void TaskForIdleMove::Wait(){
	//this_thread::sleep_for(chrono::seconds(2));
	//Sleep(5000);
	float wait_time = rand() % 2 + 1;
	clock_t start = clock();
	for (;;) {
		clock_t end = clock();
		double time = double(end - start) / CLOCKS_PER_SEC;

		if (time > wait_time)break;
	}
	
	SetIdleMove();
}

void TaskForIdleMove::CreateTimer(float wait_time) {
}

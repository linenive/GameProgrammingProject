#pragma once
#include "TaskForIdleMove.h"
#include <random>
#include <thread>

void TaskForIdleMove::ArriveTaskTarget(){

	Godot::print("[TaskForIdleMove] ARRIVE TASK: " + current_position);
	Wait();
	SetIdleMove();
}

void TaskForIdleMove::SetIdleMove(){
	Godot::print("[TaskForIdleMove] SET IDLE MOVE: "+current_position);

	//while (current_moving == false) {
		Godot::print("[TaskForIdleMove] FIND PATH ");
		SetPathList(current_position, GetNewTarget());
	//}
}

Vector2 TaskForIdleMove::GetNewTarget(){
	Vector2 random_position = current_position + Vector2(rand() % 100 + 150, rand() % 100 + 150);
	Godot::print("[TaskForIdleMove] new random target: " + random_position);
	return  random_position;
}

void TaskForIdleMove::Wait(){

	this_thread::sleep_for(chrono::seconds(2));
	Godot::print("[TaskForIdleMove] wait end ");
	//Sleep(3000);
}

void TaskForIdleMove::CreateTimer(float wait_time) {
}

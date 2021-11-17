#pragma once
#include "TaskForIdleMove.h"
#include <random>
#include <thread>

void TaskForIdleMove::ArriveTaskTarget(){

	//Wait();
	//SetIdleMove();
}


void TaskForIdleMove::SetIdleMove(){
	Godot::print("[TaskForIdleMove] SET IDLE MOVE: "+current_position);

	//while (current_moving == false) {
	SetPathList(current_position, GetNewTarget());
	//}
}

Vector2 TaskForIdleMove::GetNewTarget(){
	Vector2 random_position = current_position + Vector2(rand() % 50+30, rand() % 50 + 30);// ran(gen), ran(gen));
	Godot::print("[TaskForIdleMove] new random target: " + random_position);
	return  random_position;
}



void TaskForIdleMove::Wait(){

	this_thread::sleep_for(chrono::seconds(3));
	//Sleep(3000);
}

void TaskForIdleMove::CreateTimer(float wait_time) {
}

#pragma once
#include "Random.h"

float Number2Probability(int random_value) {
	double max = 32767;
	return random_value / max;
}

int RandomNumberBetween(int start, int end) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(start, end);
	return dis(gen);
}
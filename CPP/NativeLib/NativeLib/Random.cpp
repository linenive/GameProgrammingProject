#pragma once
#include "Random.h"

float Number2Probability(int random_value) {
	double max = 32767;
	return random_value / max;
}
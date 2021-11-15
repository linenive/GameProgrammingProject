#pragma once
#include "Random.h"

class RepeatitionRandomOccurrence {
private:
	float probability = 0.2f;

public:
	bool isOccurrence(unsigned int random_seed) {
		srand(random_seed);
		float v = Number2Probability(rand());
		return v < probability;
	}
};

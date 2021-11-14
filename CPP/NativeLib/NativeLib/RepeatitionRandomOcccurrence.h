#pragma once
#include "Random.h"

class RepeatitionRandomOccurrence {
private:
	float probability = 0.3;

public:
	bool checkOccurrence(unsigned int random_seed) {
		srand(random_seed);
		float v = Number2Probability(rand());
		printf("random1: %f %d\n", v, v<probability);
		return false;
	}
};

#pragma once
#include "Random.h"

class RepeatitionRandomOccurrence {
private:
	float probability;

public:
	void setProbability(float new_probability) {
		probability = new_probability;
	}
	bool isOccurrence(unsigned int random_seed) {
		srand(random_seed);
		float v = Number2Probability(rand());
		return v < probability;
	}
};

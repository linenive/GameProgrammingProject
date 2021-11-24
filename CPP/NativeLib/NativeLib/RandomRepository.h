#pragma once
#include <string>

const unsigned int big_prime_number = 154813283;

class RandomRepository {

private:
	TimeRepository* time_repo;
	unsigned int base_random_seed;
	unsigned int ExtractSeed(string value) {
		unsigned int new_seed = 13;
		for (int i = 0; i < value.size(); i++)
			new_seed = 31 * new_seed + (int)value[i];
		return new_seed;
	}
public:
	RandomRepository() {
		base_random_seed = ExtractSeed("banana");
	}

	int GetRandomSeedByNowTime(unsigned int overall_time) {
		return big_prime_number * (base_random_seed + overall_time);
	}
};
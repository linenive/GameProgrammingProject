#pragma once

class Timer {
private:
	float passed_time, max_time;

public:
	Timer(float max_time): passed_time(.0), max_time(max_time){}

	void TimeGo(float delta_time) {
		passed_time += delta_time;
	}

	int GetPassNumberAndReset() {
		int pass_number = passed_time / max_time;
		passed_time = passed_time - pass_number * max_time;
		return pass_number;
	}
};
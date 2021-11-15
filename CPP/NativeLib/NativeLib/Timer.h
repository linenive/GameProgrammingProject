#pragma once

class Timer {
private:
	float passed_time, max_time;

public:
	Timer(float max_time): passed_time(.0), max_time(max_time){}

	void timeGo(float delta_time) {
		passed_time += delta_time;
	}

	bool isTimeEnd() {
		return passed_time >= max_time;
	}

	void reset() {
		passed_time = .0;
	}

	bool isTimeZero() {
		return passed_time == .0;
	}
};
#include "TimeRepository.h"

void TimeRepository::TimeGo(float delta)
{
	time_update_interval.timeGo(delta);
	if (time_update_interval.isTimeEnd()) {
		now_game_time.PassOneTick();
		time_update_interval.reset();
	}
}

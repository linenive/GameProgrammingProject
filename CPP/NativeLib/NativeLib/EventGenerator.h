#pragma once
#include "Event.h"

/// <summary>
/// 난이도, 보유 재화 등을 보고 알맞은 강도의 이벤트를 발생시킨다.
/// db에서 전달받을 이벤트 형식
/// {"name": "폭염", "is_active": true, "min_difficulty": 3, "max_difficulty": 6, "appear_log_msg": "
/// </summary>
class EventGenerator {
private:
	//event_table_by_difficulty

public:
	EventGenerator() {

	}
	Event CreateEvent() {
		// 월드 정보 확인

		// 알맞은 단계의 이벤트 생성

		// 시드 + 시간을 통해 랜덤값 생성
	}

};
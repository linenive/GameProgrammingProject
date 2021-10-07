extends Label

# 노션의 '함수 목록' 문서를 이용해 UI에 필요한 데이터를 가져오는 예시입니다.

func _process(_delta):
	var text = String(get_node("/root/Main/UIManager").GetYear()) + "년 " \
		+ String(get_node("/root/Main/UIManager").GetMonth()) + "월 " \
		+ String(get_node("/root/Main/UIManager").GetDay()) + "일 " \
		+ String(get_node("/root/Main/UIManager").GetHour()) + ":" \
		+ String(get_node("/root/Main/UIManager").GetMinute())
		
	set_text(text)

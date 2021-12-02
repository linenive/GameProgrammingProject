extends Node

var ui_manager
var input_manager

func _ready():
	ui_manager = get_node("/root/Main/UIManager")
	input_manager = get_node("/root/Main/InputManager")

func _process(delta):
	#GetEventLogExample()
	pass
	
func GetEventLogExample():
	var logs = ui_manager.GetEventLogs()
	for single_log in logs:
		print(single_log[0] + ": "+single_log[1])
		print(single_log[7])
		print(String(single_log[2])+"년 "+String(single_log[3])+"월 "+\
			String(single_log[4])+"일 "+ String(single_log[5])+":"+\
			String(single_log[6]))

extends Node

var ui_manager

func _ready():
	ui_manager = get_node("/root/Main/UIManager")

func _process(delta):
	var logs = ui_manager.GetEventLogs()
	for single_log in logs:
		print(single_log[0] + ": "+single_log[1])
		print(single_log[7])
		print(String(single_log[2])+"년 "+String(single_log[3])+"월 "+\
			String(single_log[4])+"일 "+ String(single_log[5])+":"+\
			String(single_log[6]))
	#print(logs[0])
	#print(logs[1])
	#print(logs[2])

extends Node

var ui_manager


func _ready():
	ui_manager = get_node("/root/Main/UIManager")


func _process(delta):
	var logs = ui_manager.GetEventLogNames()
	print(logs[0])
	print(logs[1])
	print(logs[2])

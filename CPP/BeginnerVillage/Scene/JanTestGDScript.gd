extends Node

var ui_manager
var input_manager


func _ready():
	ui_manager = get_node("/root/Main/UIManager")
	input_manager = get_node("/root/Main/InputManager")


func _process(delta):
	var logs = ui_manager.GetEventLogNames()
	#print(logs[0])
	#print(logs[1])
	#print(logs[2])


func _on_Button2_pressed():
	input_manager.TestStructureButton()

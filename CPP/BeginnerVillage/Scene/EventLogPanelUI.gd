extends WindowDialog

var log_container : VBoxContainer

func _ready():
	log_container = $ScrollContainer/VBoxContainer
	$ScrollContainer.get_v_scrollbar().modulate = Color(0,0,0,0)

func show_event_log(logs):
	var log_ui_index = 0
	var log_ui : PanelContainer
		
	for i in range(logs.size()-1, -1, -1):
		log_ui = log_container.get_child(log_ui_index)
		log_ui.visible = true
		
		log_ui.show_log(logs[i])
		
		log_ui_index += 1	

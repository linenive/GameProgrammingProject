extends CanvasLayer

var ui_manager
var new_log_ui
var event_log_panel

func _ready():
	ui_manager = get_node("/root/Main/UIManager")
	new_log_ui = get_node("/root/Main/UIControl/LogUI/NewLogUI")
	event_log_panel = get_node("/root/Main/UIControl/LogUI/EventLogPanel")

func show_new_log():
	var logs = ui_manager.GetEventLogs()
	var log_count = logs.size()
	
	if log_count == 0:
		return

	var recent_log = logs[log_count-1]
	
	# new log ui setting
	new_log_ui.show_new_log(recent_log)

func _process(delta):
	show_new_log()
	
	if is_event_log_panel_visible():
		show_event_log()

func is_event_log_panel_visible():
	if event_log_panel.visible == true:
		return true
	else:
		return false

func show_event_log():
	var logs = ui_manager.GetEventLogs()
	event_log_panel.show_event_log(logs)
	event_log_panel.visible = true

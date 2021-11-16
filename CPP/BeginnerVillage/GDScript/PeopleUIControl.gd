extends CanvasLayer

var manage_people_ui : WindowDialog
var people_list_ui
var guest_list_ui

# Called when the node enters the scene tree for the first time.
func _ready():
	manage_people_ui = get_node("ManagePeopleUI")
	people_list_ui = get_node("ManagePeopleUI/TabContainer/People/VBoxContainer")
	guest_list_ui = get_node("ManagePeopleUI/TabContainer/Guest/VBoxContainer")
	
	$ManagePeopleUI/TabContainer/People.get_v_scrollbar().modulate = Color(0,0,0,0)
	$ManagePeopleUI/TabContainer/Guest.get_v_scrollbar().modulate = Color(0,0,0,0)
	
	open()

func open():
	manage_people_ui.show()

func _process(delta):
	# character repository => list update
	pass

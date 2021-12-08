extends WindowDialog

var uicontrol
var static_unit_manager

var target_id = 0
var target_type

# Called when the node enters the scene tree for the first time.
func _ready():
	uicontrol = get_node("/root/Main/UIControl")
	static_unit_manager = get_node("/root/Main/StaticUnitManager")

func show_popup(id, type, info, window_position:Vector2):
	if target_id == 0:
		setting_popup(id, type)
	
	set_position(window_position)	
	
	var btn = get_close_button()
	btn.connect("pressed", self, "close_button_pressed")
	
	show_info_by_type(id, info)
	
	show()

func show_info_by_type(id, info):
	$CharacterInfo.visible = false
	$ItemInfo.visible = false
	$BuildingInfo.visible = false
	
	#$BuildingInfo.visible = true
	#$BuildingInfo.window_setting_building_info(target_node, info)
	
	if(target_type == "Character"):
		$CharacterInfo.visible = true
		$CharacterInfo.window_setting_character_info(id, info)
	elif(target_type == "Building"):
		$BuildingInfo.visible = true
		$BuildingInfo.window_setting_building_info(id, info)

func _process(delta):
	if uicontrol.is_used_popup(self):
		if target_type == "Character":
			show_info_by_type(target_id, uicontrol.get_character_info(target_id))
		#elif target_type == "Building":
			#show_info_by_type(target_id, static_unit_manager.GetBuildingInfo(target_id))

func init_popup():
	target_id = 0
	target_type = ""

func setting_popup(id, type):
	target_id = id
	target_type = type

func close_button_pressed():
	init_popup()
	uicontrol.close_info_popup(self)

func _gui_input(event):
	if event is InputEventMouseButton and event.pressed and event.button_index == BUTTON_LEFT:
		uicontrol.set_ui_top(self)

func get_target_id():
	return target_id

func get_target_type():
	return target_type

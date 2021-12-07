extends Control

var ui_control
var static_unit_manager
var popup_ui

var target_object_id

var guest_info_ui_array : Array
var resident_info_ui_array : Array

# Called when the node enters the scene tree for the first time.
func _ready():
	guest_info_ui_array.append($GuestInfo)
	guest_info_ui_array.append($HBoxContainer/GuestInfo)
	
	resident_info_ui_array.append($ResidentInfo)
	resident_info_ui_array.append($HBoxContainer/ResidentInfo)
	
	popup_ui = get_parent()
	ui_control = get_node("/root/Main/UIControl")
	static_unit_manager = get_node("/root/Main/StaticUnitManager")

func get_target_object_id():
	return target_object_id

func window_setting_character_info(node_character, info):
	target_object_id = node_character.get_id()
	var character = node_character as Sprite
	
	$VBoxContainer/HBoxContainer/content_character_first_name.text = info["first_name"]
	$VBoxContainer/HBoxContainer/content_character_last_name.text = info["last_name"]
	$VBoxContainer/HBoxContainer4/content_character_gender.text = info["gender"]
	$VBoxContainer/HBoxContainer3/content_character_position.text = position_to_string(node_character.get_position())
	$character_texture.texture = character.texture
	
	$title_inventory.text = "Inventory"
	$InventorySlot/VBoxContainer/content_item_name.text = info["item1"][0]
	$InventorySlot/VBoxContainer/content_item_type.text = info["item1"][1]
	
	window_setting_guest_info()
	
	#if "guest 인지":
	#	window_setting_guest_info()
	#else:
	#	window_setting_resident_info()

func window_setting_guest_info():
	get_parent().set_title("Guest Info")	
	$title_character_info.text = "Guest Info"
	
	for ui in guest_info_ui_array:
		ui.visible = true
	
	for ui in resident_info_ui_array:
		ui.visible = false

func window_setting_resident_info():
	get_parent().set_title("Resident Info")	
	$title_character_info.text = "Resident Info"
	
	for ui in guest_info_ui_array:
		ui.visible = false
	
	for ui in resident_info_ui_array:
		ui.visible = true

func position_to_string(position):
	var x = round(position.x)
	var y = round(position.y)
	
	return "(" + str(x) + ", " + str(y) + ")"

func _on_recruit_btn_pressed():
	print("recruit")
	if static_unit_manager.RecruitGuestAsResident(target_object_id):
		popup_ui.close_button_pressed()
		popup_ui.hide()

func _on_track_btn_pressed():
	ui_control.popup_ui_track_btn_pressed(popup_ui.target_node.get_path())

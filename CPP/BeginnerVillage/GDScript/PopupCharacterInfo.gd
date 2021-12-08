extends Control

var ui_control
var static_unit_manager
var popup_ui

var target_character_id
var target_character_node

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

func get_character_node(id):
	var character_pool = get_node("/root/Main/JanTestGDScript/TestTileCreater/Character")
	
	for character in character_pool.get_children():
		if character.get_id() == id:
			return character
	
	return null

func get_target_character_id():
	return target_character_id

func window_setting_character_info(id, info):
	target_character_id = id
	target_character_node = get_character_node(id)
	
	$VBoxContainer/HBoxContainer/content_character_name.text = info["full_name"]
	$VBoxContainer/HBoxContainer4/content_character_gender.text = info["gender"]
	$VBoxContainer/HBoxContainer3/content_character_position.text = position_to_string(target_character_node.get_position())
	$character_texture.texture = (target_character_node as Sprite).texture
	
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
	if static_unit_manager.RecruitGuestAsResident(target_character_id):
		popup_ui.close_button_pressed()
		popup_ui.hide()

func _on_track_btn_pressed():
	ui_control.popup_ui_track_btn_pressed(target_character_node.get_path())

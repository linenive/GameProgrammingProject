extends Node

var world_manager
var confirmation_dialog

func _ready():
	world_manager = get_node("/root/Main/WorldManager")
	confirmation_dialog = get_node("/root/Main/UIControl/ConfirmationDialog")
	
	$VBoxContainer/HBoxContainer2/VillageNameEditBtn.connect("pressed", self, "edit_village_name")
	
	show_village_name()
	show_money()

func _process(delta):
	show_time()

func show_village_name():
	$VBoxContainer/HBoxContainer2/VillageName.text = world_manager.GetVillageName()
	pass

func show_money():
	$VBoxContainer/HBoxContainer/Money.text = String(world_manager.GetMoney())
	pass

func edit_village_name():
	confirmation_dialog.init_confirmation_dialog("Village Name Edit", "Enter new village name.", "Village name...")
	pass

func set_village_name(name):
	world_manager.SetVillageName(name)
	show_village_name()

func show_time():
	var year = get_node("/root/Main/UIManager").GetYear()
	var month = get_node("/root/Main/UIManager").GetMonth()
	var day = get_node("/root/Main/UIManager").GetDay()
	var hour = get_node("/root/Main/UIManager").GetHour()
	var minute = get_node("/root/Main/UIManager").GetMinute()
	
	var date_str = "%d년 %02d월 %02d일 %02d:%02d" % [year, month, day, hour, minute]
		
	$VBoxContainer/HBoxContainer3/Time.text = date_str

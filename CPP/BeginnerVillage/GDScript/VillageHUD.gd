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
	show_money()

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
	var year = str(get_node("/root/Main/UIManager").GetYear())+"년"
	var month = str(get_node("/root/Main/UIManager").GetMonth())+"월"
	var day = str(get_node("/root/Main/UIManager").GetDay())+"일"
	var hour = "%02d" %[get_node("/root/Main/UIManager").GetHour()]
	#var hour_str = "%02d" %[hour]
	var minute = "%02d" %[get_node("/root/Main/UIManager").GetMinute()]
	
	$VBoxContainer/HBoxContainer3/TimeHBox/Year.text = year
	$VBoxContainer/HBoxContainer3/TimeHBox/Month.text = month
	$VBoxContainer/HBoxContainer3/TimeHBox/Day.text = day
	$VBoxContainer/HBoxContainer3/TimeHBox/Hour.text = hour
	$VBoxContainer/HBoxContainer3/TimeHBox/Minute.text = minute

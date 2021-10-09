extends Node2D

onready var g_namelabel = get_node("Label")
onready var g_following_button = get_node("FollowNPCButton")
onready var g_close_button = get_node("CloseButton")

func _ready():
	CloseNpcInfoUIButtons()

func CloseNpcInfoUIButtons():
	DeactiveFollowingButton()
	DeactiveCloseButton()
	DeactiveNameLabel()
func ActiveNpcInfoUIButtons():
	ActiveFollowingButton()
	ActiveCloseButton()
	#ActiveNameLabel()
	
func ActiveNameLabel():
	g_namelabel.disabled=false
func DeactiveNameLabel():
	g_namelabel.text =""
func ActiveFollowingButton():
	g_following_button.disabled=false
func DeactiveFollowingButton():
	g_following_button.disabled=true
func ActiveCloseButton():
	g_close_button.disabled=false
func DeactiveCloseButton():
	g_close_button.disabled=true

func ActiveNewNpcInfoUI(name):
	g_namelabel.text = name
	ActiveNpcInfoUIButtons()

func GetNpcName():
	return g_namelabel.text

func _on_FollowNPCButton_pressed():
	get_node("root/UIManager").StartNPCTrace(self.get_path())

func _on_CloseButton_pressed():
	CloseNpcInfoUIButtons()

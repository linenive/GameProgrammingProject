extends Node2D

onready var g_stopfollowing_button = get_node("UILayer/StopFollowing")

var g_ui_list =[]
var g_nowchild_index=0
var g_maxchild_index=1

func _ready():
	InitUIManagerSetting()

func InitUIManagerSetting():
	SetNpcInfoUIList()
	g_maxchild_index = len(g_ui_list)-1
	DeactiveStopFollowingButton()
	g_nowchild_index=0

func SetNpcInfoUIList():
	g_ui_list.append(get_node("NpcInfoUI"))
	g_ui_list.append(get_node("NpcInfoUI2"))

func ActiveStopFollowingButton():
	g_stopfollowing_button.disabled=false
func DeactiveStopFollowingButton():
	g_stopfollowing_button.disabled=true

func SetNowActiveNpcUIInfo(name):
	if (g_ui_list[g_nowchild_index].GetNpcName() !=name):
		g_ui_list[g_nowchild_index].ActiveNewNpcInfoUI(name)	
		UpdateNowChildIndex()
		
func UpdateNowChildIndex():
	if g_nowchild_index>g_maxchild_index:
		g_nowchild_index = 0
	else:
		g_nowchild_index+=1
		
func StartNPCTrace(name):
	ActiveStopFollowingButton()

func _on_StopFollowing_pressed():
	DeactiveStopFollowingButton()

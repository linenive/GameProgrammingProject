extends CanvasLayer

# NPC들을 눌렀을 때 정보 UI창을 띄워주는 매니저가 있고, 각각에 따라가기 아이콘(예:돋보기모양)이 있다고 가정.
# 상위의 매니저가 UI창들의 리스트를 가지고 있고, 입력 신호를 받았을 때 노드의 정보를 UI창으로 넘긴다고 생각

onready var g_stopfollowing_button = get_node("StopFollowing")
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


	

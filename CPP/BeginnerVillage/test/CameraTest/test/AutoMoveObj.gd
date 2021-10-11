extends Area2D

export var g_distance=200
export var g_target=0

onready var g_uiwindowmanager = get_tree().get_current_scene().get_node("UIWindowManager")
onready var g_cameramanager = get_tree().get_current_scene().get_node("CameraManager")
onready var g_direction=1
onready var g_mypath = get_path()

func _ready():
	g_target = position.x + g_distance * g_direction
	
func _process(_delta):
	if position.x == g_target:
		g_direction = g_direction * -1
		g_target = position.x + g_direction * g_distance
	else:
		position.x += g_direction

# 실제로 사용되는 부분 - 클릭됐을시 자신의 path를 넘겨주는 함수
func _on_AutoMoveObj_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.button_index == BUTTON_LEFT and event.is_pressed():
			g_uiwindowmanager.StartNPCTrace(name)
			g_cameramanager.SetCameraSetting_Trace(g_mypath)

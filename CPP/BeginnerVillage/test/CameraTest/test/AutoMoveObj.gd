extends Area2D

export var g_distance=200
export var g_target=0
onready var g_direction=1
onready var g_mypath = get_path()

func _ready():
	g_target=position.x+g_distance*g_direction
	
func _process(_delta):
	if position.x == g_target:
		g_direction = g_direction * -1
		g_target = position.x + g_direction * g_distance
	else:
		position.x += g_direction

func _input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.button_index == BUTTON_LEFT and event.pressed:
			ClickAndTraceStart()
	
# 실제로 사용되는 부분 - 클릭됐을시 자신의 path를 넘겨주는 함수	
func ClickAndTraceStart():
	get_node("/root/YojinTest/UIWindowManager").StartNPCTrace(name)
	get_node("/root/YojinTest/CameraManager").SetCameraSetting_Trace(g_mypath)

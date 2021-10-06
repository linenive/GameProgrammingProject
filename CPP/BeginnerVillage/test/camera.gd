extends Node2D

export (Vector2)var nowAddVector = Vector2(0,0)
export (Vector2)var nowScreenSize = Vector2(0,0)
export var level=0
export var speed = 10
func _ready():
	nowScreenSize=get_viewport().get_visible_rect().size
	level=$CanvasLayer.getSkillLevel()
	print(level)
	$Camera2D.SetScreenSize(nowScreenSize)

func _input(ev):
	if ev.is_key_pressed("ui_left"):
		$Camera2D.CameraMove_Left()
	if ev.is_key_pressed("ui_right"):
		$Camera2D.CameraMove_Right()
	if ev.is_key_pressed("ui_up"):
		$Camera2D.CameraMove_Up()
	if ev.is_key_pressed("ui_down"):
		$Camera2D.CameraMove_Down()
		
	nowAddVector = $Camera2D.GetAddVector()
	position = nowAddVector.normalized() * speed

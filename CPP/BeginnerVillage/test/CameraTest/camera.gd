extends Node2D

export (Vector2)var nowPosition = Vector2(0,0)
export (Vector2)var nowScreenSize = Vector2(0,0)

export var level=0
export var speed = 10

var velocity = Vector2()
func _ready():
	nowScreenSize=get_viewport().get_visible_rect().size
	$Camera2D.SetScreenSize(nowScreenSize)
	
func _process(_delta):
	$Camera2D.position = $EmptyCamera.position

func SetCameraTarget(pos):
	$Camera2D.SetTarget(pos)
	
func ReleaseCameraTarget(pos):
	$Camera2D.ReleaseTarget(pos)



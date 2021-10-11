extends Node2D

export var speed = 4
var velocity=Vector2()

func _process(_delta):
	DetectKey()

func DetectKey():
	velocity=Vector2(0,0)
	if Input.is_action_pressed("ui_left"):
		velocity.x=-speed
	elif Input.is_action_pressed("ui_right"):
		velocity.x=speed
	position += velocity

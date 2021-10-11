extends Node2D

export var speed=3
var target = 100
var direction=1

signal randomMovingObj

func _process(_delta):
	
	if(position.x == target):
		direction = direction *-1
		target= 100*direction
	else:
		position.x+=direction

func _input(ev):
	if ev is InputEventMouseButton:
		emit_signal("randomMovingObj")

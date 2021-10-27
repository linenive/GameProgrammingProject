extends Node2D

var now_index
var max_index
var now_moving = false
var speed =3

var pathlist
var target :Vector2
var velocity : Vector2;
var dir_vector:Vector2;
func _ready():
	var rect_size = get_viewport_rect().size;
	$PathfindingManager.InitMap(rect_size.x,rect_size.y)
	print($PathfindingManager.linktest)
	max_index = $PathfindingManager.GetPathLength()
	pathlist = $PathfindingManager.ResultPaths
	print(pathlist)
	$NPC.position = pathlist[0]
	now_index=1
	target = pathlist[now_index]
	now_moving = true

func _process(_delta):
	dir_vector = target-$NPC.position
	var distance = $NPC.position.distance_to(target)
	$CanvasLayer/Label.text = str(distance)
	if distance <2:
		$NPC.position = target
		now_index+=1
		if now_index >= max_index:
			now_moving=false
		else:
			target = pathlist[now_index]
	
	if now_moving:
		velocity = (dir_vector).normalized()*speed
		$NPC.position+=velocity
		

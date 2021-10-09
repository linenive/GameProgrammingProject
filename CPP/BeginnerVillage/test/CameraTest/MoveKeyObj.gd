extends Node2D

export var g_speed=3
export var g_velocity=Vector2()

var g_screen_size
var g_unmoving_interval=20
export (Vector2)var g_unmoving_size

var g_canmovecamera=true
func _ready():
	g_screen_size = get_viewport_rect().size	
	g_unmoving_size = g_screen_size-Vector2(g_unmoving_interval,g_unmoving_interval)

func _process(_delta):
	if(g_canmovecamera):
		CameraMovewithKey()
		CameraMovewithMouse()	

func CameraMovewithKey():
	DetectKeyPress()
	if g_velocity.length()>0:
		g_velocity = g_velocity.normalized()*g_speed
		position+=g_velocity
		
func DetectKeyPress():
	g_velocity = Vector2(0,0)
	if Input.is_action_pressed("ui_left"):
		g_velocity.x-=1
	if Input.is_action_pressed("ui_right"):
		g_velocity.x+=1
	if Input.is_action_pressed("ui_up"):
		g_velocity.y-=1
	if Input.is_action_pressed("ui_down"):
		g_velocity.y+=1

func CameraMovewithMouse():
	var nowmousevector = get_viewport().get_mouse_position()

	var addPos = Vector2(0,0)
	if (nowmousevector.x<g_unmoving_interval):
		addPos.x=-1
	elif (nowmousevector.x>g_unmoving_size.x):
		addPos.x=1	
	if (nowmousevector.y<g_unmoving_interval):
		addPos.y=-1
	elif (nowmousevector.y>g_unmoving_size.y):
		addPos.y=1

	position += addPos*g_speed

func ActiveCanMoveCamera():
	g_canmovecamera = true
func DeactiveCanMoveCamera():
	g_canmovecamera = false
#screen  boundary를 벗어나지 않게 수정
	

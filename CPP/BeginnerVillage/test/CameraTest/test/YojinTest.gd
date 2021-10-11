extends Navigation2D

# Member variables
const SPEED = 20.0

var begin = Vector2()
var end = Vector2()
var path = []

func _process(delta):
	if (path.size() > 1):
		var to_walk = delta*SPEED
		while(to_walk > 0 and path.size() >= 2):
			var pfrom = path[path.size() - 1]
			var pto = path[path.size() - 2]
			var d = pfrom.distance_to(pto)
			if (d <= to_walk):
				path.remove(path.size() - 1)
				to_walk -= d
			else:
				path[path.size() - 1] = pfrom.linear_interpolate(pto, to_walk/d)
				to_walk = 0

		var atpos = path[path.size() - 1]
		get_node("player").move_and_slide(atpos)

		if (path.size() < 2):
			path = []
			set_process(false)
	else:
		set_process(false)
	
func update_path():
	var col_polygon = get_node("obstacle").get_node("Collider").polygon
	var navi_polygon = get_node("NavigationPolygonInstance").get_navigation_polygon()
	var polygon = NavigationPolygonInstance.new()
	#polygon.navpoly.add_outline(get_node("obstacle").get_node("Collider").polygon)
	#polygon.navpoly.make_polygons_from_outlines()
	polygon.navpoly.set_vertices(get_node("obstacle").get_node("Collider").polygon)
	navi_polygon.navpoly = polygon
	
	var p = get_simple_path(begin, end, true)
	path = Array(p) 
	path.invert()

	set_process(true)

func _input(event):
	if event is InputEventMouseButton:
		if event.button_index == BUTTON_LEFT and event.is_pressed():
			begin = get_node("player").position
			# Mouse to local navigation coordinates
			end = get_viewport().get_mouse_position() - position
			update_path()

func _ready():
	set_process_input(true)
	#update_path()

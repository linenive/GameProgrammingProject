extends CanvasLayer

var main_btns = []
var current_clicked_btn

# Called when the node enters the scene tree for the first time.
func _ready():
	for child in self.get_child(0).get_children():
		main_btns.append(child)
	
	for btn in main_btns:
		btn.connect("pressed", self, "button_clicked", [btn])

func button_clicked(clicked_btn):
	for btn in main_btns:
		if clicked_btn == btn:
			if current_clicked_btn == btn:
				current_clicked_btn = null
				btn.get_child(0).visible = false
			else:
				current_clicked_btn = btn
				btn.get_child(0).visible = true
		else:
			btn.get_child(0).visible = false
			pass

func memu_clicked():
	print("menu")
	pass

func people_clicked():
	print("people")
	pass

func construction_clicked():
	print("construction")
	pass

func research_clicked():
	print("research")
	pass

extends CanvasLayer

export var level = 0
export var testName = 'noname'
export var testDataA = 0
export var testDataB = false

func _process(_delta):
	$testLabel.text = String($test.getSkillLevel()) + String($test.getTestDataA())
	level = $test.getSkillLevel()
	testDataA = $test.getTestDataA()
	testDataB = $test.getTestDataB()

#include "TestManager.h"

void TestManager::_register_methods(){
	register_method("_ready", &TestManager::_ready);
	register_method("_process", &TestManager::_process);
	register_method("_physics_process", &TestManager::_physics_process);
	register_method("pull", &TestManager::pull);

	register_method("getSkillLevel", &TestManager::getSkillLevel);
	register_method("getSkillName", &TestManager::getSkillName);
	register_method("getTestDataA", &TestManager::getTestDataA);
	register_method("getTestDataB", &TestManager::getTestDataB);

	register_method("SetScreenSize", &TestManager::SetScreenSize);
	register_method("SetTarget", &TestManager::SetTarget);
	register_method("ReleaseTarget", &TestManager::ReleaseTarget);
	register_property<TestManager, int>("skilLevel", &TestManager::test_c, 10);

	register_property<TestManager, float>("screenBounds_left", &TestManager::screenBounds_left, 0);
	register_property<TestManager, float>("screenBounds_right", &TestManager::screenBounds_right, 0);
	register_property<TestManager, float>("screenBounds_up", &TestManager::screenBounds_up, 0);
	register_property<TestManager, float>("screenBounds_down", &TestManager::screenBounds_down, 0);
}

void TestManager::_init(){

}

void TestManager::_ready(){
	skill = Skill(5, "µµº®");
	skill.SetData(456, true);
}

void TestManager::_process(float delta){
	skill.SetData(789, true);
}

void TestManager::_physics_process(float delta){
}

void TestManager::pull(Variant from, float magnitude){
}

void TestManager::DetectScreenBounds(Vector2 newScreenSize){
	screenBounds_left = -newScreenSize.x;
	screenBounds_right = newScreenSize.x;
	screenBounds_up = -newScreenSize.y;
	screenBounds_down = newScreenSize.y;
}

void TestManager::SetScreenSize(Vector2 nowScreenSize) {
	DetectScreenBounds(nowScreenSize);
}

void TestManager::SetTarget(Vector2 pos) {
}

void TestManager::ReleaseTarget(Vector2 pos) {
}


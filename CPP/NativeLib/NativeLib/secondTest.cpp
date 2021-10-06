#include "secondTest.h"

void secondTest::_register_methods()
{
    register_method("_process", &secondTest::_process);
}

void secondTest::_process(float delta)
{
    time_passed += delta;

    Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));

    set_position(new_position);
}

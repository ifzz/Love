#pragma once

#include <lua.h>

void l_mouse_register(lua_State* state);
void l_mouse_pressed(int x, int y, int button);
void l_mouse_released(int x, int y, int button);

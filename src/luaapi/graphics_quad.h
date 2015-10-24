#pragma once

#include <stdbool.h>
#include <lua.h>
#include "../graphics/quad.h"

int l_graphics_newQuad(lua_State* state);
void l_graphics_quad_register(lua_State* state);
bool l_graphics_isQuad(lua_State* state, int index);
graphics_Quad* l_graphics_toQuad(lua_State* state, int index);


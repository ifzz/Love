#pragma once

#include <stdbool.h>
#include <lua.h>
#include "../graphics/font.h"

void l_graphics_font_register(lua_State* state);
bool l_graphics_isFont(lua_State* state, int index);
int l_graphics_newFont(lua_State* state);
graphics_Font* l_graphics_toFont(lua_State* state, int index);

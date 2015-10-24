#include <lauxlib.h>
#include "../graphics/graphics.h"
#include "graphics_window.h"
#include "tools.h"


static int l_graphics_window_getWidth(lua_State* state) {
  lua_pushnumber(state, graphics_getWidth());
  return 1;
}

static int l_graphics_window_getHeight(lua_State* state) {
  lua_pushnumber(state, graphics_getHeight());
  return 1;
}

static luaL_Reg const windowFreeFuncs[] = {
  {"getWidth", l_graphics_window_getWidth},
  {"getHeight", l_graphics_window_getHeight},
  {NULL, NULL}
};

void l_graphics_window_register(lua_State* state) {
  l_tools_registerModule(state, "window", windowFreeFuncs);
}


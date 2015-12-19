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

static int l_graphics_window_setTitle(lua_State* state){
  graphics_setTitle(lua_tostring(state, 1));
  return 1;
}

static int l_graphics_window_setMode(lua_State* state){
  graphics_setMode(lua_tointeger(state, 1), lua_tointeger(state, 2));
  return 1;
}

static int l_graphics_window_setFullscreen(lua_State* state){
  graphics_setFullscreen(lua_toboolean(state, 1), lua_tostring(state, 2));
  return 1;
}

static int l_graphics_window_isCreated(lua_State* state){
  lua_pushboolean(state,graphics_isCreated());
  return 1;
}

static int l_graphics_window_getTitle(lua_State* state){
  lua_pushstring(state, graphics_getTitle());
  return 1;
}

static int l_graphics_window_setPosition(lua_State* state){
  graphics_setPosition(lua_tointeger(state, 1), lua_tointeger(state, 2));
  return 1;
}

static int l_graphics_window_hasFocus(lua_State* state){
  lua_pushinteger(state, graphics_hasFocus());
  return 1;
}

static luaL_Reg const windowFreeFuncs[] = {
  {"setFullscreen", l_graphics_window_setFullscreen},
  {"setMode", l_graphics_window_setMode},
  {"isCreated", l_graphics_window_isCreated},
  {"setTitle", l_graphics_window_setTitle},
  {"getTitle", l_graphics_window_getTitle},
  {"setPosition", l_graphics_window_setPosition},
  {"getWidth", l_graphics_window_getWidth},
  {"getHeight", l_graphics_window_getHeight},
  {"hasFocus",  l_graphics_window_hasFocus},
  {NULL, NULL}
};

void l_graphics_window_register(lua_State* state) {
  l_tools_registerModule(state, "window", windowFreeFuncs);
}


#include "../mouse.h"
#include "tools.h"


static struct {
  lua_State *luaState;
} moduleData;


static int l_mouse_isVisible(lua_State *state) {
  lua_pushboolean(state, mouse_isVisible());
  return 1;
}


static int l_mouse_isDown(lua_State *state) {
  const char *name = luaL_checkstring(state, 1);
  int res = mouse_isDown(name);
  if(res < 0) {
    luaL_error(state, "bad button name '%s'", name);
  }
  lua_pushboolean(state, res);
  return 1;
}


static int l_mouse_getPosition(lua_State *state) {
  int x, y;
  mouse_getPosition(&x, &y);
  lua_pushinteger(state, x);
  lua_pushinteger(state, y);
  return 2;
}


static int l_mouse_getX(lua_State *state) {
  lua_pushinteger(state, mouse_getX());
  return 1;
} 


static int l_mouse_getY(lua_State *state) {
  lua_pushinteger(state, mouse_getY());
  return 1;
} 


static int l_mouse_setPosition(lua_State *state) {
  int x = luaL_checknumber(state, 1);
  int y = luaL_checknumber(state, 2);
  mouse_setPosition(x, y);
  return 0;
} 


static int l_mouse_setVisible(lua_State *state) {
  mouse_setVisible(lua_toboolean(state, 1));
  return 0;
}


static int l_mouse_setX(lua_State *state) {
  int x = luaL_checknumber(state, 1);
  mouse_setX(x);
  return 0;
} 


static int l_mouse_setY(lua_State *state) {
  int y = luaL_checknumber(state, 1);
  mouse_setY(y);
  return 0;
} 

static luaL_Reg const regFuncs[] = {
  { "isDown",         l_mouse_isDown        },
  { "isVisible",      l_mouse_isVisible     },
  { "getPosition",    l_mouse_getPosition   },
  { "getX",           l_mouse_getX          },
  { "getY",           l_mouse_getY          },
  { "setPosition",    l_mouse_setPosition   },
  { "setVisible",     l_mouse_setVisible    },
  { "setX",           l_mouse_setX          },
  { "setY",           l_mouse_setY          },
  { NULL, NULL }
};


void l_mouse_register(lua_State* state) {
  moduleData.luaState = state;
  l_tools_registerModule(state, "mouse", regFuncs);
}

static const char* intButtonToString(int button)
{
  if(button == 1)
    return "l";
  else if(button == 2)
    return "m";
  else if(button == 3)
    return "r";

  return "";
}

void l_mouse_pressed(int x, int y, int button){
  lua_getglobal(moduleData.luaState, "love");
  lua_pushstring(moduleData.luaState, "mousepressed");
  lua_rawget(moduleData.luaState, -2);
  lua_pushinteger(moduleData.luaState, x);
  lua_pushinteger(moduleData.luaState, y);
  lua_pushstring(moduleData.luaState, intButtonToString(button));
  lua_call(moduleData.luaState, 3, 0);
  lua_settop(moduleData.luaState, lua_gettop(moduleData.luaState));
}

void l_mouse_released(int x, int y, int button){
  lua_getglobal(moduleData.luaState, "love");
  lua_pushstring(moduleData.luaState, "mousereleased");
  lua_rawget(moduleData.luaState, -2);
  lua_pushinteger(moduleData.luaState, x);
  lua_pushinteger(moduleData.luaState, y);
  lua_pushstring(moduleData.luaState, intButtonToString(button));
  lua_call(moduleData.luaState, 3, 0);
  lua_settop(moduleData.luaState, lua_gettop(moduleData.luaState));
}

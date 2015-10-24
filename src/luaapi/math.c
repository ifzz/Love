#include "tools.h"
#include "math.h"
#include "../math/random.h"

int l_math_random(lua_State* state) {
  float lo = 0.0f, hi = 1.0f;
  int t = lua_gettop(state);
  switch(t) {
  case 1:
    hi = l_tools_toNumberOrError(state, 1);
    break;

  case 2:
    lo = l_tools_toNumberOrError(state, 1);
    hi = l_tools_toNumberOrError(state, 2);
    break;
  }

  lua_pushnumber(state, math_random(lo, hi));
  return 1;
}


static luaL_Reg const mathFreeFuncs[] = {
  {"random", l_math_random},
  {NULL, NULL}
};

void l_math_register(lua_State* state) {
  l_tools_registerModule(state, "math", mathFreeFuncs);
}

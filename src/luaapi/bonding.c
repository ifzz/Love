#include <lualib.h>
#include "bonding.h"
#include "../bonding.h"

int l_bonding_getVersion(lua_State* state) {
  bonding_Version const * version = bonding_getVersion();
  lua_pushnumber(state, version->major);
  lua_pushnumber(state, version->minor);
  lua_pushnumber(state, version->revision);
  lua_pushstring(state, version->codename);
  return 4;
}

int l_bonding_register(lua_State* state) {
  lua_newtable(state);

  lua_pushstring(state, "getVersion");
  lua_pushcfunction(state, l_bonding_getVersion);
  lua_rawset(state, -3);
  
  lua_setglobal(state, "love");

  luaL_openlibs(state);

  return 0;
}

#include <stdlib.h>
#include <lauxlib.h>
#include "filesystem.h"
#include "tools.h"
#include "../filesystem/filesystem.h"

  
static int l_filesystem_read(lua_State* state) {
  // TODO implement max length
  char const* filename = l_tools_toStringOrError(state, 1);
  char* data = NULL;
  int len = filesystem_read(filename, &data);
  if(len < 0) {
    lua_pushstring(state, "could not read file");
    return lua_error(state);
  }

  lua_pushstring(state, data);
  free(data);
  lua_pushnumber(state, len);
  return 2;
}


static int l_filesystem_load(lua_State* state) {
  char const* filename = l_tools_toStringOrError(state, 1);
  char* data = NULL;
  int len = filesystem_read(filename, &data);
  if(len < 0) {
    lua_pushstring(state, "could not read file");
    return lua_error(state);
  }

  luaL_loadstring(state, data);
  free(data);
  return 1;
}

static luaL_Reg const regFuncs[] = {
  {"load", l_filesystem_load},
  {"read", l_filesystem_read},
  {NULL, NULL}
};

int l_filesystem_register(lua_State* state) {
  l_tools_registerModule(state, "filesystem", regFuncs);
  return 0;
}

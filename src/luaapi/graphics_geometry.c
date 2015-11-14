#include "graphics_geometry.h"
#include "../graphics/geometry.h"
#include "tools.h"
#include "../tools/log.c"

static struct {
  float * vertices;
  float vertSize;
} moduleData;

static int l_geometry_rectangle(lua_State* state) {
  const char* type = l_tools_toStringOrError(state, 1);
  float x = l_tools_toNumberOrError(state, 2);
  float y = l_tools_toNumberOrError(state, 3);
  float w = l_tools_toNumberOrError(state, 4);
  float h = l_tools_toNumberOrError(state, 5);

  if (strncmp(type,"line",4) == 0)
    graphics_geometry_drawRectangle(x, y, w, h);
  else if(strncmp(type,"fill", 4) == 0)
    graphics_geometry_fillRectangle(x, y, w, h);

  return 0;
}

static int l_geometry_setLineWidth(lua_State* state) {
  float width = l_tools_toNumberOrError(state, 1);
  graphics_geometry_setLineWidth(width);
  return 0;
}

static int l_geometry_getLineWidth(lua_State* state) {
  lua_pushnumber(state, graphics_geometry_getLineWidth());
  return 1;
}

static luaL_Reg const geometryFuncs[] = {
  {"rectangle",    l_geometry_rectangle},
  {"setLineWidth", l_geometry_setLineWidth},
  {"getLineWidth", l_geometry_getLineWidth},
  {NULL,NULL}
};

void l_graphics_geometry_register(lua_State* state) {
  l_tools_registerFuncsInModule(state, "graphics", geometryFuncs);
}

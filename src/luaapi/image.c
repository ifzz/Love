#include <lauxlib.h>
#include "image.h"
#include "tools.h"
#include "../image/imagedata.h"

static struct {
  int imageDataMT;
} moduleData;


int l_image_newImageData(lua_State* state) {
  image_ImageData* imageData = (image_ImageData*)lua_newuserdata(state, sizeof(image_ImageData));
  int s1type = lua_type(state, 1);
  if(s1type == LUA_TSTRING) {
    image_ImageData_new_with_filename(imageData, lua_tostring(state, 1));
  } else if(s1type == LUA_TNUMBER && lua_type(state, 2) == LUA_TNUMBER) {
    image_ImageData_new_with_size(imageData, lua_tointeger(state, 1), lua_tointeger(state, 2));
  } else {
    lua_pushstring(state, "need filename or size for imagedata");
    return lua_error(state);
  }

  lua_rawgeti(state, LUA_REGISTRYINDEX, moduleData.imageDataMT);
  lua_setmetatable(state, -2);

  return 1;
}

static int l_image_gcImageData(lua_State* state) {
  image_ImageData* imagedata = (image_ImageData*)lua_touserdata(state, 1);
  image_ImageData_free(imagedata);
  return 0;
}

static luaL_Reg const regFuncs[] = {
  {"newImageData", l_image_newImageData},
  {NULL, NULL}
};

l_checkTypeFn(l_image_isImageData, moduleData.imageDataMT)
l_toTypeFn(l_image_toImageData, image_ImageData)

static luaL_Reg const imageDataMetatableFuncs[] = {
  {"__gc", l_image_gcImageData},
  {NULL, NULL}
};

int l_image_register(lua_State* state) {
  l_tools_registerModule(state, "image", regFuncs);

  moduleData.imageDataMT = l_tools_makeTypeMetatable(state, imageDataMetatableFuncs);
  
  return 0;
}

#pragma once

#include <lua.h>
#include <stdbool.h>
#include "../image/imagedata.h"

bool l_image_isImageData(lua_State* state, int index);
image_ImageData* l_image_toImageData(lua_State* state, int index);
int l_image_register(lua_State* state);
int l_image_newImageData(lua_State* state);

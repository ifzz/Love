#pragma once

#include <stdbool.h>
#include <lua.h>
#include "../graphics/batch.h"

typedef struct {
  graphics_Batch batch;
  int textureRef;
} l_graphics_Batch;

int l_graphics_newSpriteBatch(lua_State* state);
void l_graphics_batch_register(lua_State* state);
bool l_graphics_isBatch(lua_State* state, int index);
l_graphics_Batch* l_graphics_toBatch(lua_State* state, int index);

#pragma once
#include <lua.h>
#include "../graphics/shader.h"

typedef struct {
  graphics_Shader shader;
  int *referencedTextures;
} l_graphics_Shader;

//int l_graphics_newShader(lua_State* state);
void l_graphics_shader_register(lua_State *state);
bool l_graphics_isShader(lua_State* state, int index);
l_graphics_Shader* l_graphics_toShader(lua_State* state, int index);

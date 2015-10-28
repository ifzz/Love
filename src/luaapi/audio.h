#pragma once

#include <lua.h>
#include <stdbool.h>
#include "../audio/audio.h"
#include "../audio/staticsource.h"

typedef enum {
  audio_SourceType_static,
  audio_SourceType_stream
} audio_SourceType;

int l_audio_register(lua_State *state);
bool l_audio_isStaticSource(lua_State* state, int index);
bool l_audio_isStreamSource(lua_State* state, int index);

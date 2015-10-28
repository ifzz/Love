#include "tools.h"
#include "audio.h"

static struct {
  int audioDataMT;
} moduleData;

static int l_audio_newSource(lua_State *state) {
  char const* filename = l_tools_toStringOrError(state, 1);

  audio_StaticSource *src = lua_newuserdata(state, sizeof(audio_StaticSource));
  audio_loadStatic(src, filename);

  lua_rawgeti(state, LUA_REGISTRYINDEX, moduleData.audioDataMT);
  lua_setmetatable(state, -2);
  return 1;
}

static int l_audio_SourceCommon_play(lua_State* state) {
  audio_SourceCommon* source = (audio_SourceCommon*)lua_touserdata(state, 1);
  audio_SourceCommon_play(source);
  return 0;
}

static int l_audio_SourceCommon_setVolume(lua_State *state) {
  float gain = l_tools_toNumberOrError(state, 2);
  audio_SourceCommon *source = (audio_SourceCommon*)lua_touserdata(state, 1);
  audio_SourceCommon_setVolume(source, gain);
  return 0;
}

static int l_audio_SourceCommon_getVolume(lua_State *state) {
  audio_SourceCommon *source = (audio_SourceCommon*)lua_touserdata(state, 1);
  lua_pushnumber(state, audio_SourceCommon_getVolume(source));
  return 1;
}

static luaL_Reg const SourceMetatableFuncs[] = {
  {"play",       l_audio_SourceCommon_play},
  {"setVolume",  l_audio_SourceCommon_setVolume},
  {"getVolume",  l_audio_SourceCommon_getVolume},
  {NULL, NULL}
};

static luaL_Reg const regFuncs[] = {
  {"newSource", l_audio_newSource},
  {NULL, NULL}
};

int l_audio_register(lua_State *state) {
  l_tools_registerModule(state, "audio", regFuncs);
  moduleData.audioDataMT = l_tools_makeTypeMetatable(state, SourceMetatableFuncs);
  return 1;
}

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

static int l_audio_SourceCommon_stop(lua_State* state) {
  audio_SourceCommon* source = (audio_SourceCommon*)lua_touserdata(state, 1);
  audio_SourceCommon_stop(source);
  return 0;
}

static int l_audio_SourceCommon_pause(lua_State* state) {
  audio_SourceCommon* source = (audio_SourceCommon*)lua_touserdata(state, 1);
  audio_SourceCommon_pause(source);
  return 0;
}

static int l_audio_SourceCommon_resume(lua_State* state) {
  audio_SourceCommon* source = (audio_SourceCommon*)lua_touserdata(state, 1);
  audio_SourceCommon_resume(source);
  return 0;
}

static int l_audio_SourceCommon_isStopped(lua_State* state) {
  audio_SourceCommon* source = (audio_SourceCommon*)lua_touserdata(state, 1);
  audio_SourceCommon_isStopped(source);
  return 0;
}

static int l_audio_SourceCommon_isPlaying(lua_State* state) {
  audio_SourceCommon* source = (audio_SourceCommon*)lua_touserdata(state, 1);
  audio_SourceCommon_isPlaying(source);
  return 0;
}

static int l_audio_SourceCommon_isPaused(lua_State* state) {
  audio_SourceCommon* source = (audio_SourceCommon*)lua_touserdata(state, 1);
  audio_SourceCommon_isPaused(source);
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

static int l_audio_setVolumeGlobal(lua_State* state){
  double volume = lua_tonumber(state, 1);
  if(volume <= 0.0f)
    volume = 0.0f;
  else if (volume >= 1.0f)
    volume = 1.0f;
  audio_setVolume(volume);
  return 1;
}

static int l_audio_SourceCommon_setPitch(lua_State *state) {
  float pitch = l_tools_toNumberOrError(state, 2);
  audio_SourceCommon *source = (audio_SourceCommon*)lua_touserdata(state, 1);
  audio_SourceCommon_setPitch(source, pitch);
  return 0;
}

static int l_audio_SourceCommon_getPitch(lua_State *state) {
  audio_SourceCommon *source = (audio_SourceCommon*)lua_touserdata(state, 1);
  lua_pushnumber(state, audio_SourceCommon_getPitch(source));
  return 1;
}

static luaL_Reg const SourceMetatableFuncs[] = {
  {"setPitch",   l_audio_SourceCommon_setPitch},
  {"getPitch",   l_audio_SourceCommon_getPitch},
  {"play",       l_audio_SourceCommon_play},
  {"setVolume",  l_audio_SourceCommon_setVolume},
  {"getVolume",  l_audio_SourceCommon_getVolume},
  {"isPlaying",  l_audio_SourceCommon_isPlaying},
  {"isPaused",  l_audio_SourceCommon_isPaused},
  {"isStopped",  l_audio_SourceCommon_isStopped},
  {"pause",  l_audio_SourceCommon_pause},
  {"resume",  l_audio_SourceCommon_resume},
  {"stop",  l_audio_SourceCommon_stop},
  {NULL, NULL}
};

static luaL_Reg const regFuncs[] = {
  {"newSource", l_audio_newSource},
  {"setVolume", l_audio_setVolumeGlobal},
  {NULL, NULL}
};

int l_audio_register(lua_State *state) {
  l_tools_registerModule(state, "audio", regFuncs);
  moduleData.audioDataMT = l_tools_makeTypeMetatable(state, SourceMetatableFuncs);
  return 1;
}

#include "keyboard.h"
#include "../keyboard.h"
#include "tools.h"

static struct {
  lua_State *luaState;
  bool keyRepeat;

} moduleData;


int l_keyboard_hasKeyRepeat(lua_State* state) {
  lua_pushboolean(state, moduleData.keyRepeat);
  return 1;
}

int l_keyboard_setKeyRepeat(lua_State* state) {
  moduleData.keyRepeat = lua_toboolean(state, 1);
  return 0;
}

int l_keyboard_isDown(lua_State* state) {
  bool any = false;
  int top = lua_gettop(state); 
  for(int i = 0; i < top; ++i) {
    any = any || keyboard_ispressed(
                  keyboard_getKeycode(
                    l_tools_toStringOrError(state, i + 1)));
    if(any) {
      break;
    }
  }

  lua_pushboolean(state, any);
  return 1;
}

int l_keyboard_setTextInput(lua_State* state) {
  bool enable = lua_toboolean(state, 1);
  if(enable) {
    keyboard_startText();
  } else {
    keyboard_stopText();
  }
  return 0;
}

int l_keyboard_hasTextInput(lua_State* state) {
  lua_pushboolean(state, keyboard_isTextEnabled());
  return 1;
}

static luaL_Reg const regFuncs[] = {
  {"hasKeyRepeat", l_keyboard_hasKeyRepeat},
  {"setKeyRepeat", l_keyboard_setKeyRepeat},
  {"isDown",       l_keyboard_isDown},
  {"setTextInput", l_keyboard_setTextInput},
  {"hasTextInput", l_keyboard_hasTextInput},
  {NULL, NULL}
};

void l_keyboard_register(lua_State* state) {
  moduleData.luaState = state;
  moduleData.keyRepeat = false;

  l_tools_registerModule(state, "keyboard", regFuncs);
}

void l_keyboard_keypressed(SDL_Keycode key, bool isrepeat) {
  if(isrepeat && !moduleData.keyRepeat) {
    return;
  }
  lua_getglobal(moduleData.luaState, "love");
  lua_pushstring(moduleData.luaState, "keypressed");
  lua_rawget(moduleData.luaState, -2);
  lua_pushstring(moduleData.luaState, keyboard_getKeyName(key));
  lua_pushboolean(moduleData.luaState, isrepeat);
  lua_call(moduleData.luaState, 2, 0);
}

void l_keyboard_keyreleased(SDL_Keycode key) {
  lua_getglobal(moduleData.luaState, "love");
  lua_pushstring(moduleData.luaState, "keyreleased");
  lua_rawget(moduleData.luaState, -2);
  lua_pushstring(moduleData.luaState, keyboard_getKeyName(key));
  lua_call(moduleData.luaState, 1, 0);
}

void l_keyboard_textInput(char const* text) {
  lua_getglobal(moduleData.luaState, "love");
  lua_pushstring(moduleData.luaState, "textinput");
  lua_rawget(moduleData.luaState, -2);
  lua_pushstring(moduleData.luaState, text);
  lua_call(moduleData.luaState, 1, 0);
}

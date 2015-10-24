#pragma once

#include <stdbool.h>
#include <lua.h>
# include <SDL_keycode.h>
void l_keyboard_register(lua_State* state);
void l_keyboard_keypressed(SDL_Keycode key, bool repeat);
void l_keyboard_keyreleased(SDL_Keycode key);
void l_keyboard_textInput(char const* text);

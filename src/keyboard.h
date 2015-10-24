#pragma once
#include <SDL_keyboard.h>
#include <stdbool.h>

void keyboard_init(void);
char const * keyboard_getKeyName(SDL_Keycode key);
void keyboard_keypressed(SDL_Keycode key);
void keyboard_keyreleased(SDL_Keycode key);
SDL_Keycode keyboard_getKeycode(char const* name);
bool keyboard_ispressed(SDL_Keycode key);
void keyboard_startText(void);
void keyboard_stopText(void);
bool keyboard_isTextEnabled(void);
void keyboard_textInput(char const* text);

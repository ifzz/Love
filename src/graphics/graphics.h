#pragma once

#include <stdbool.h>
#include "image.h"
#include "quad.h"
#include "../math/vector.h"

void graphics_init(int width, int height);

typedef enum {
  graphics_BlendMode_additive,
  graphics_BlendMode_alpha,
  graphics_BlendMode_subtractive,
  graphics_BlendMode_multiplicative,
  graphics_BlendMode_premultiplied,
  graphics_BlendMode_replace,
  graphics_BlendMode_screen
} graphics_BlendMode;


void graphics_setBackgroundColor(float red, float green, float blue, float alpha);
void graphics_setColor(float red, float green, float blue, float alpha);
float* graphics_getColor(void);
float* graphics_getBackgroundColor(void);
void graphics_clear(void);
void graphics_swap(void);
void graphics_drawArray(graphics_Quad const* quad, mat4x4 const* tr2d, GLuint ibo, GLuint count, GLenum type, GLenum indexType, float const * useColor, float ws, float hs);

//Window
int mouse_focus;
int graphics_hasMouseFocus();
int graphics_setMouseFocus(int value);
int focus;
int graphics_hasFocus();
int graphics_setFocus(int value);
int graphics_getWidth(void);
int graphics_getHeight(void);
int graphics_setTitle(const char* title);
int graphics_setMode(int width, int height);
int graphics_setFullscreen(int value, const char* mode);
int graphics_isCreated();
const char* graphics_getTitle();
int graphics_setPosition(int x, int y);

void graphics_setColorMask(bool r, bool g, bool b, bool a);
void graphics_getColorMask(bool *r, bool *g, bool *b, bool *a);
graphics_BlendMode graphics_getBlendMode();
void graphics_setBlendMode(graphics_BlendMode mode);
void graphics_clearScissor(void);
void graphics_setScissor(int x, int y, int w, int h);
bool graphics_getScissor(int *x, int *y, int *w, int *h);
void graphics_reset(void);

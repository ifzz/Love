#pragma once

typedef struct {
  float x;
  float y;
  float w;
  float h;
} graphics_Quad;

void graphics_Quad_new(graphics_Quad *dst, float x, float y, float w, float h);
void graphics_Quad_newWithRef(graphics_Quad *dst, float x, float y, float w, float h, float rw, float rh);

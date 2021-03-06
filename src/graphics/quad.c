#include "quad.h"

void graphics_Quad_new(graphics_Quad *dst, float x, float y, float w, float h) {
  dst->x = x;
  dst->y = y;
  dst->w = w;
  dst->h = h;
}

void graphics_Quad_newWithRef(graphics_Quad *dst, float x, float y, float w, float h, float rw, float rh) {
  graphics_Quad_new(dst, x / rw, y / rh, w / rw, h / rh);
}

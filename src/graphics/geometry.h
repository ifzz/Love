#pragma once

#include "graphics.h"

typedef enum {
  graphics_DrawMode_fill,
  graphics_DrawMode_line
}graphics_DrawMode;

void graphics_geometry_init();

void graphics_geometry_fillRectangle(float x, float y, float w, float h);
void graphics_geometry_drawRectangle(float x, float y, float w, float h);

void graphics_geometry_setLineWidth(float width);
float graphics_geometry_getLineWidth();

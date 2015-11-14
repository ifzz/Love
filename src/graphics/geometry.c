#include <tgmath.h>
#include <stdlib.h>
#include "../math/util.h"
#include "geometry.h"
#include "graphics.h"
#include "shader.h"
#include "matrixstack.h"
#include "../tools/log.c"
#include "../image/imagedata.h"

static struct {
  unsigned int dataVBO;
  unsigned int dataIBO;
  float* data;
  unsigned short* index;
  float lineWidth;
  graphics_Shader plainColorShader;
  int currentDataSize;
  int currentIndexSize;
} moduleData;

void graphics_geometry_init(){
  glGenBuffers(1,&moduleData.dataIBO);
  glGenBuffers(1,&moduleData.dataVBO);
  glBindBuffer(GL_ARRAY_BUFFER, moduleData.dataVBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, moduleData.dataIBO);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(2*sizeof(float)));
  moduleData.lineWidth = 1.0f;
  graphics_Shader_new(&moduleData.plainColorShader, NULL,
                      "vec4 effect(vec4 color, Image texture, vec2 texture_coords, vec2 screen_cords ) {\n"
                      "  return color;\n"
                      "}\n");
}

static void growBuffers(int vertices, int indices){
  int dataSize = vertices * 6 * sizeof(float);
  if(moduleData.currentDataSize < dataSize){
    free(moduleData.data);
    moduleData.data = (float*)malloc(dataSize);
    moduleData.currentDataSize = dataSize;
  }
  int indexSize = indices * sizeof(unsigned short);
  if(moduleData.currentIndexSize < indexSize){
    free(moduleData.index);
    moduleData.index = (unsigned short*)malloc(indexSize);
    moduleData.currentIndexSize = indexSize;
  }
}

static void drawBuffer(int vertices, int indices, GLenum type){
  glBindBuffer(GL_ARRAY_BUFFER, moduleData.dataVBO);
  glBufferData(GL_ARRAY_BUFFER, vertices*6*sizeof(float), moduleData.data, GL_DYNAMIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, moduleData.dataIBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices*sizeof(unsigned short),moduleData.index, GL_DYNAMIC_DRAW);

  graphics_Shader* shader = graphics_getShader();
  graphics_setShader(&moduleData.plainColorShader);
  mat4x4 tr;
  m4x4_newIdentity(&tr);

  graphics_Quad quad = {0,0,1,1};
  graphics_drawArray(&quad,&tr,moduleData.dataIBO, indices, type, GL_UNSIGNED_SHORT, graphics_getColor(), 1, 1);

  graphics_setShader(shader);

}

void graphics_geometry_fillRectangle(float x, float y, float w, float h){
  growBuffers(8, 10);

  float *buf = moduleData.data;
  float hh = h * .5f;
  float hw = w * .5f;

  // top left
  buf[0] = x;
  buf[1] = y;

  buf[6] = x + hw;
  buf[7] = y + hh;

  float x2 = x + w * .5f;
  float y2 = y + h * .5f;

  // top right
  buf[12] = x2 + hw;
  buf[13] = y;

  buf[18] = x2;
  buf[19] = y + hh;

  // bottom right
  buf[24] = x2 + hw;
  buf[25] = y2 + hh;

  buf[30] = x;
  buf[31] = y2;

  // bottom left
  buf[36] = x;
  buf[37] = y2 + hh;

  buf[42] = x;
  buf[43] = y2;

  for(int i = 0; i < 8; ++i) {
    for(int j = 2; j < 6; ++j) {
      buf[6*i+j] = 1.0f;
    }
    moduleData.index[i] = i;
  }
  moduleData.index[8] = 0.0f;
  moduleData.index[9] = 1.0f;

  drawBuffer(8, 10, GL_TRIANGLE_STRIP);
}

void graphics_geometry_drawRectangle(float x, float y, float w, float h) {
  growBuffers(8, 10);

  float *buf = moduleData.data;
  float lwh = moduleData.lineWidth * .5f;

  // top left
  buf[0] = x - lwh;
  buf[1] = y - lwh;

  buf[6] = x + lwh;
  buf[7] = y + lwh;

  float x2 = x + w;
  float y2 = y + h;

  // top right
  buf[12] = x2 + lwh;
  buf[13] = y  - lwh;

  buf[18] = x2 - lwh;
  buf[19] = y  + lwh;

  // bottom right
  buf[24] = x2 + lwh;
  buf[25] = y2 + lwh;

  buf[30] = x2 - lwh;
  buf[31] = y2 - lwh;

  // bottom left
  buf[36] = x - lwh;
  buf[37] = y2 + lwh;

  buf[42] = x + lwh;
  buf[43] = y2 - lwh;

  for(int i = 0; i < 8; ++i) {
    for(int j = 2; j < 6; ++j) {
      buf[6*i+j] = 1.0f;
    }
    moduleData.index[i] = i;
  }
  moduleData.index[8] = 0;
  moduleData.index[9] = 1;

  drawBuffer(8, 10, GL_TRIANGLE_STRIP);
}


float graphics_geometry_getLineWidth(void) {
  return moduleData.lineWidth;
}

void graphics_geometry_setLineWidth(float width) {
  moduleData.lineWidth = width;
}

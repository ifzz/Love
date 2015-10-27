#include "image.h"
#include "../image/imagedata.h"
#include "../math/vector.h"
#include "graphics.h"
#include "vertex.h"
#include "shader.h"

static struct {
  GLuint imageVBO;
  GLuint imageIBO;
} moduleData;

static graphics_Vertex const imageVertices[] = {
  {{0.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
  {{1.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
  {{0.0f, 1.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
  {{1.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}
};

void graphics_image_init(void) {
  glGenBuffers(1, &moduleData.imageVBO);
  glGenBuffers(1, &moduleData.imageIBO);

  unsigned char const imageIndices[] = { 0, 1, 2, 3 };

  glBindBuffer(GL_ARRAY_BUFFER, moduleData.imageVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(imageVertices), imageVertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, moduleData.imageIBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(imageIndices), imageIndices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(graphics_Vertex), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(graphics_Vertex), (GLvoid const*)(2*sizeof(float)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(graphics_Vertex), (GLvoid const*)(4*sizeof(float)));
}

static const graphics_Wrap defaultWrap = {
  .verMode = graphics_WrapMode_clamp,
  .horMode = graphics_WrapMode_clamp
};

static const graphics_Filter defaultFilter = {
  .maxAnisotropy = 1.0f,
  .mipmapLodBias = 1.0f,
  .minMode = graphics_FilterMode_linear,
  .magMode = graphics_FilterMode_linear,
  .mipmapMode = graphics_FilterMode_none
};

void graphics_Image_new_with_ImageData(graphics_Image *dst, image_ImageData *data) {
  glGenTextures(1, &dst->texID);
  glBindTexture(GL_TEXTURE_2D, dst->texID);
  graphics_Image_setFilter(dst, &defaultFilter);

  graphics_Image_setWrap(dst, &defaultWrap);

  graphics_Image_refresh(dst, data);
}

void graphics_Image_refresh(graphics_Image *img, image_ImageData const *data) {
  glBindTexture(GL_TEXTURE_2D, img->texID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data->w, data->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data->surface);
  img->width = data->w;
  img->height = data->h;
}

void graphics_Image_free(graphics_Image *obj) {
  glDeleteTextures(1, &obj->texID);
}

void graphics_Image_setFilter(graphics_Image *img, graphics_Filter const* filter) {
  graphics_Texture_setFilter(img->texID, filter);
}

void graphics_Image_getFilter(graphics_Image *img, graphics_Filter *filter) {
  graphics_Texture_getFilter(img->texID, filter);
}

void graphics_Image_setWrap(graphics_Image *img, graphics_Wrap const* wrap) {
  glBindTexture(GL_TEXTURE_2D, img->texID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap->horMode);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap->verMode);
}

void graphics_Image_getWrap(graphics_Image *img, graphics_Wrap *wrap) {
  glBindTexture(GL_TEXTURE_2D, img->texID);
  glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int*)&wrap->horMode);
  glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int*)&wrap->verMode);
}

void graphics_Image_draw(graphics_Image const* image, graphics_Quad const* quad,
                         float x, float y, float r, float sx, float sy,
                         float ox, float oy, float kx, float ky) {

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, image->texID);
  mat4x4 tr2d;
  m4x4_newTransform2d(&tr2d, x, y, r, sx, sy, ox, oy, kx, ky);
  glBufferData(GL_ARRAY_BUFFER, sizeof(imageVertices), imageVertices, GL_DYNAMIC_DRAW);
//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof imageVertices, imageVertices);
  graphics_drawArray(quad, &tr2d,  moduleData.imageIBO, 4, GL_TRIANGLE_STRIP, GL_UNSIGNED_BYTE, graphics_getColor(), image->width * quad->w, image->height * quad->h);
  
}

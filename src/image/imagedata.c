#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../3rdparty/stb/stb_image.c"
#include "imagedata.h"


void image_ImageData_new_with_filename(image_ImageData *dst, char const* filename) {
  int n;
  dst->surface = stbi_load(filename, &dst->w, &dst->h, &n, 4);
}

void image_ImageData_new_with_size(image_ImageData *dst, int width, int height) {
  dst->surface = malloc(width*height*4);
  memset(dst->surface, 0, width*height*4);
}

void image_ImageData_free(image_ImageData *data) {
  free(data->surface);
}

void image_init() {
}

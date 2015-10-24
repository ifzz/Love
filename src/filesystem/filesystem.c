#include "filesystem.h"
#include <stdio.h>
#include <stdlib.h>

void filesystem_init(void) {

}

int filesystem_read(char const* filename, char** output) {
  FILE* infile = fopen(filename, "r");
  if(!infile) {
    return -1;
  }

  fseek(infile, 0, SEEK_END);
  long size = ftell(infile);
  rewind(infile);

  *output = malloc(size+1);
  fread(*output, size, 1, infile);
  fclose(infile);
  (*output)[size] = 0;
  return size;
}

#include <stdlib.h>
#include "random.h"

float math_random(float min, float max) {
  return ((float)rand()) / RAND_MAX * (max - min) + min;
}

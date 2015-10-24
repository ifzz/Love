#include <stdlib.h>
#include "random.h"


float math_random(float min, float max) {
  // TODO implement more sophisticated pseudo random and imitate love
  return ((float)rand()) / RAND_MAX * (max - min) + min;
}

#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "randomgenerator.h"
#include "util.h"
#include <inttypes.h>


static uint64_t wangHash64(uint64_t key) {
  key = (~key) + (key << 21); // key = (key << 21) - key - 1;
  key = key ^ (key >> 24);
  key = (key + (key << 3)) + (key << 8); // key * 265
  key = key ^ (key >> 14);
  key = (key + (key << 2)) + (key << 4); // key * 21
  key = key ^ (key >> 28);
  key = key + (key << 31);
  return key;
}


void RandomGenerator_init(RandomGenerator *r) {
  RandomGenerator_Seed s;
  s.b32.low = 0xCBBF7A44;
  s.b32.high = 0x0139408D;
  RandomGenerator_setSeed(r, s);
  r->lastRandomNormal = INFINITY;
}


void RandomGenerator_setSeed(RandomGenerator *r, RandomGenerator_Seed s) {
  r->seed = s;
  do {
    s.b64 = wangHash64(s.b64);
  } while (s.b64 == 0);
  r->state = s;
}


RandomGenerator_Seed RandomGenerator_getSeed(RandomGenerator *r) {
  return r->seed;
}


void RandomGenerator_getState(RandomGenerator *r, char *dst) {
  sprintf(dst, "0x%016" PRIx64, r->state.b64);
}


int RandomGenerator_setState(RandomGenerator *r, const char *src) {
  uint64_t n;
  int res = sscanf(src, "0x%" PRIx64, &n);
  if (res != 1) {
    return -1;
  }
  r->state.b64 = n;
  return 0;
}


uint64_t RandomGenerator_rand(RandomGenerator *r) {
  r->state.b64 ^= (r->state.b64 << 13);
  r->state.b64 ^= (r->state.b64 >> 7);
  r->state.b64 ^= (r->state.b64 << 17);
  return r->state.b64;
}


double RandomGenerator_random(RandomGenerator *r) {
  return RandomGenerator_rand(r) / ((double) (UINT64_MAX) + 1.0);
}


double RandomGenerator_random1(RandomGenerator *r, double max) {
  return RandomGenerator_random(r) * max;
}


double RandomGenerator_random2(RandomGenerator *r, double min, double max) {
  return RandomGenerator_random(r) * (max - min) + min;
}


double RandomGenerator_randomNormal(RandomGenerator *r, double stddev) {

  if (r->lastRandomNormal != INFINITY) {
    double n = r->lastRandomNormal;
    r->lastRandomNormal = INFINITY;
    return n * stddev;
  }

  double n = sqrt(-2.0 * log(1. - RandomGenerator_random(r)));
  double phi = 2.0 * PI * (1. - RandomGenerator_random(r));
  
  r->lastRandomNormal = n * cos(phi);
  return n * sin(phi) * stddev;
}


double RandomGenerator_randomNormal2(RandomGenerator *r, double stddev, double mean) {
  return RandomGenerator_randomNormal(r, stddev) + mean;
}

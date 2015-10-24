#pragma once

#include <stdint.h>

#define RANDOMGENERATOR_STATE_STR_SZ (19)

typedef union {
  uint64_t b64;
  struct {
    uint32_t low;
    uint32_t high;
  } b32;
} RandomGenerator_Seed;

typedef struct {
  RandomGenerator_Seed seed;
  RandomGenerator_Seed state;
  double lastRandomNormal;
} RandomGenerator;


void RandomGenerator_init(RandomGenerator *r);
void RandomGenerator_setSeed(RandomGenerator *r, RandomGenerator_Seed s);
RandomGenerator_Seed RandomGenerator_getSeed(RandomGenerator *r);
void RandomGenerator_getState(RandomGenerator *r, char *dst);
int RandomGenerator_setState(RandomGenerator *r, const char *src);
uint64_t RandomGenerator_rand(RandomGenerator *r);
double RandomGenerator_random(RandomGenerator *r);
double RandomGenerator_random1(RandomGenerator *r, double max);
double RandomGenerator_random2(RandomGenerator *r, double min, double max);
double RandomGenerator_randomNormal(RandomGenerator *r, double stddev);
double RandomGenerator_randomNormal2(RandomGenerator *r, double stddev, double mean);


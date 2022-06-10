#include "RandomUtils.h"

RandomUtils::RandomUtils() {}


void RandomUtils::randomSeed() {
   srand(time(0));
}

float RandomUtils::getRandomInt(int lower, int upper) {
   return (rand() % (upper - lower + 1)) + lower;
}

float RandomUtils::getRandomFloat(float lower, float upper) {
   float random = ((float) rand()) / (float) RAND_MAX;
   float diff = upper - lower;
   float r = random * diff;
   return lower + r;
}

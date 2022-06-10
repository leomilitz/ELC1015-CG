#ifndef RANDOMUTILS_H
#define RANDOMUTILS_H

#include <stdlib.h>
#include <time.h>

class RandomUtils
{
   public:
      RandomUtils();
      void randomSeed();
      float getRandomInt(int lower, int upper);
      float getRandomFloat(float lower, float upper);
};

#endif // RANDOMUTILS_H

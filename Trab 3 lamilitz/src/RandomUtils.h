/*
   RandomUtils
   Autor: Leonardo Militz

   Classe utilitária para a geração de números aleatórios.
   ---------------------------------------------------------------------------
   - randomSeed: Cria uma seed para o programa com base no time(0).
   - getRandomInt: Gera um número inteiro aleatório entre outros dois inteiros.
   - getRandomFloat: Gera um número float aleatório entre outros dois float.
*/

#ifndef RANDOMUTILS_H
#define RANDOMUTILS_H

#include <stdlib.h>
#include <time.h>

class RandomUtils {
   public:
      RandomUtils();
      void randomSeed();
      float getRandomInt(int lower, int upper);
      float getRandomFloat(float lower, float upper);
};

#endif // RANDOMUTILS_H

/*
   RandomUtils
   Autor: Leonardo Militz

   Classe utilit�ria para a gera��o de n�meros aleat�rios.
   ---------------------------------------------------------------------------
   - randomSeed: Cria uma seed para o programa com base no time(0).
   - getRandomInt: Gera um n�mero inteiro aleat�rio entre outros dois inteiros.
   - getRandomFloat: Gera um n�mero float aleat�rio entre outros dois float.
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

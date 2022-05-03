/*
   Color Histogram
   Autor: Leonardo Militz

   Classe que representa o histograma de cores que recebe os dados de cor da imagem
   selecionada. Ele exibe os canais de cores e a luminância com base em quais estão
   ativos. O histograma realiza a escala do eixo X de forma que a visualização
   continue a mesma independentemente do tamanho da tela, e a escala do eixo Y com
   base no valor de cor mais recorrente, garantindo uma boa visualização na tela.
   --------------------------------------------------------------------------------
   - setSizeYScale: define a escala do eixo Y com base no valor de cor mais recorrente
   nos canais de cor.
*/

#ifndef COLORHISTOGRAM_H
#define COLORHISTOGRAM_H

#include <vector>

#include "image.h"

class ColorHistogram {
   public:
      ColorHistogram(int x, int y, int length, int height);

      void draw();
      void clearHistogram();

      void setColorValues(std::vector<int> &values, char color);
      void setActiveChannels(bool r, bool g, bool b, bool l);
      void setSizeYScale(int highestValue);

   private:
      int x, y, length, height;
      float sizeYScale, sizeXScale;
      bool plotRed, plotGreen, plotBlue, plotLuminance;
      std::vector<int> redValues, greenValues, blueValues, luminanceValues;
};

#endif // COLORHISTOGRAM_H

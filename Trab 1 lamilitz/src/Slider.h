/*
   Slider
   Autor: Leonardo Militz

   Slider � uma implementa��o gen�rica de um UIComponent que representa um slider.
   � recebido um range, e a partir desse range, ele retornar� um valor inteiro
   para ser utilizado em outras classes. Sua callback � chamada toda vez que o slider
   � movido. Por padr�o, o slider inicia com 50% de seu range total. Tanto a posi��o
   atual quanto a descri��o do slider s�o apresentadas na tela em tempo de execu��o.
*/

#ifndef SLIDER_H
#define SLIDER_H

#include "UIComponent.h"

class Slider: public UIComponent {
   public:
      Slider(int startValue, int endValue, int x, int y, int length, int height, std::string caption, std::function<void()> action);

      void render();
      void inputManagement(int mouseX, int mouseY, int *mouseState);

      void setValue(int value);
      int getValue();

      bool canGetValue;
      std::string caption;

   private:
      void sliderDrag(Vector2 *posMouse);
      void updatePosition(int x);

      int value, startValue, endValue, length, charSize, btnLength, btnHeight, currentValue;
      float currentPosition;
      bool isHolding;
      Vector2 *btnPos1, *btnPos2, *offset;
};

#endif // SLIDER_H

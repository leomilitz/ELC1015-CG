/*
   Slider
   Autor: Leonardo Militz

   Slider é uma implementação genérica de um UIComponent que representa um slider.
   É recebido um range, e a partir desse range, ele retornará um valor inteiro
   para ser utilizado em outras classes. Sua callback é chamada toda vez que o slider
   é movido. Por padrão, o slider inicia com 50% de seu range total. Tanto a posição
   atual quanto a descrição do slider são apresentadas na tela em tempo de execução.
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

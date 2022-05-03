/*
   Slider
   Autor: Leonardo Militz

   Slider � uma implementa��o gen�rica de um slider usando a API Canvas2D. Ele recebe
   um range, e a partir desse range, ele retornar� um valor inteiro para ser utilizado
   em outras classes. Ele guarda uma fun��o callback (fun��o lambda registrada na
   classe UIManager) que ir� ser chamada toda vez que o usu�rio mover o slider. Por
   padr�o, o slider inicia com 50% de seu range total. Tanto a posi��o atual quanto
   a descri��o do slider s�o apresentadas na tela.
*/

#ifndef SLIDER_H
#define SLIDER_H

#include <functional>

#include "gl_canvas2d.h"

class Slider {
   public:
      Slider(int startValue, int endValue, int x, int y, int length, std::string &caption, std::function<void()> &action);

      void draw();
      void checkInput(int mouseX, int mouseY, int *mouseState);

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
      Vector2 *startPos, *btnPos1, *btnPos2, *offset;
      std::function<void()> action;
};

#endif // SLIDER_H

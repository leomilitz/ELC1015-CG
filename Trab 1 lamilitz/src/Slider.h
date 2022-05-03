/*
   Slider
   Autor: Leonardo Militz

   Slider é uma implementação genérica de um slider usando a API Canvas2D. Ele recebe
   um range, e a partir desse range, ele retornará um valor inteiro para ser utilizado
   em outras classes. Ele guarda uma função callback (função lambda registrada na
   classe UIManager) que irá ser chamada toda vez que o usuário mover o slider. Por
   padrão, o slider inicia com 50% de seu range total. Tanto a posição atual quanto
   a descrição do slider são apresentadas na tela.
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

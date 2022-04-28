/*
   Classe gen�rica que implementa um bot�o na API Canvas2D.

   A biblioteca "functional" de C++ � usada para fazer fun��es callback serem
   chamadas ao clicar no bot�o; dessa forma, cada bot�o pode funcionar de forma
   espec�fica dependendo da fun��o que foi linkada ao chamar o construtor.
*/

#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <functional>

#include "gl_canvas2d.h"
#include "ImageEditor.h"

class Button {
   public:
      enum State { clicked, hovered, standard, toggled };
      enum Color { grey, red, green, blue, light };

      Button(Vector2 *v1, Vector2 *v2, std::string text, std::function<void ()> action, Color color, bool canToggle);
      void draw(State state);
      State checkCollision(int mouseX, int mouseY, int mouseState);
      void onClick();
      std::string getCaption();
      void setToggled(bool isToggled);
   private:
      Vector2 *v1, *v2, *edge;
      int charHalfSize;                         // Metade do tamanho lateral do caractere do texto
      std::string text;                         // texto do bot�o
      std::function<void()> action;             // a��o do bot�o
      Color btnColor;
      bool isToggled, canToggle;

      void drawHover();                         // efeito on hover do bot�o
      void drawDefault();                       // visual padr�o do bot�o
      void drawClick();                         // visual do bot�o ao ser clicado
      void drawEdge(float r, float g, float b);
};

#endif // BUTTON_H

/*
   Classe genérica que implementa um botão na API Canvas2D.

   A biblioteca "functional" de C++ é usada para fazer funções callback serem
   chamadas ao clicar no botão; dessa forma, cada botão pode funcionar de forma
   específica dependendo da função que foi linkada ao chamar o construtor.
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
      std::string text;                         // texto do botão
      std::function<void()> action;             // ação do botão
      Color btnColor;
      bool isToggled, canToggle;

      void drawHover();                         // efeito on hover do botão
      void drawDefault();                       // visual padrão do botão
      void drawClick();                         // visual do botão ao ser clicado
      void drawEdge(float r, float g, float b);
};

#endif // BUTTON_H

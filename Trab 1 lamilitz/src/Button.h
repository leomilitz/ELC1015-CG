/*
   Button

   Classe gen�rica que implementa um bot�o na API Canvas2D. A biblioteca "functional"
   de C++ � usada para fazer fun��es callback (fun��es lambda registradas no UIManager)
   serem chamadas ao clicar no bot�o; dessa forma, cada bot�o pode funcionar de forma
   espec�fica dependendo da fun��o que foi linkada (binded) ao chamar o construtor.
   O bot�o possui quatro visuais diferentes: clicked, hovered, standard e toggled.
   Cada um desses visuais ser� renderizado de forma diferente dependendo do estado do mouse
   em rela��o ao bot�o. Existem tamb�m 5 estilos de bot�o: grey, red, green, blue e light.
   O texto em display do bot�o � centralizado com base no seu tamanho.
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

      Button(Vector2 *v1, Vector2 *v2, std::string &caption, std::function<void()> &action, Color color, bool canToggle);
      void draw(State state);
      State checkCollision(int mouseX, int mouseY, int mouseState);
      void onClick();
      std::string getCaption();
      void setToggled(bool isToggled);

   private:
      Vector2 *v1, *v2, *edge;
      int charHalfSize;                         // Metade do tamanho lateral do caractere do texto
      std::string caption;                      // texto do bot�o
      std::function<void()> action;             // a��o do bot�o
      Color btnColor;
      bool isToggled, canToggle;

      void drawHover();                         // efeito on hover do bot�o
      void drawDefault();                       // visual padr�o do bot�o
      void drawClick();                         // visual do bot�o ao ser clicado ou toggled
      void drawEdge(float r, float g, float b);
};

#endif // BUTTON_H

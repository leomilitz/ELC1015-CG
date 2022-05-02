/*
   Button

   Classe genérica que implementa um botão na API Canvas2D. A biblioteca "functional"
   de C++ é usada para fazer funções callback (funções lambda registradas no UIManager)
   serem chamadas ao clicar no botão; dessa forma, cada botão pode funcionar de forma
   específica dependendo da função que foi linkada (binded) ao chamar o construtor.
   O botão possui quatro visuais diferentes: clicked, hovered, standard e toggled.
   Cada um desses visuais será renderizado de forma diferente dependendo do estado do mouse
   em relação ao botão. Existem também 5 estilos de botão: grey, red, green, blue e light.
   O texto em display do botão é centralizado com base no seu tamanho.
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
      std::string caption;                      // texto do botão
      std::function<void()> action;             // ação do botão
      Color btnColor;
      bool isToggled, canToggle;

      void drawHover();                         // efeito on hover do botão
      void drawDefault();                       // visual padrão do botão
      void drawClick();                         // visual do botão ao ser clicado ou toggled
      void drawEdge(float r, float g, float b);
};

#endif // BUTTON_H

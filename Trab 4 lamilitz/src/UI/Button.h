/**
 *  Button
 *  Autor: Leonardo Militz
 *
 *  Classe genérica derivada de UIComponent que implementa um botão na API Canvas2D.
 *  O botão possui quatro visuais diferentes: clicked, hovered, standard e toggled.
 *  Cada um desses visuais será renderizado de forma diferente dependendo do estado do mouse
 *  em relação ao botão. Existem também 5 estilos de botão: grey, red, green, blue e light.
 *  O texto em display do botão é centralizado com base no seu tamanho.
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "UIComponent.h"

class Button: public UIComponent {
   public:
      enum State { clicked, hovered, standard, toggled };
      enum Color { grey, red, green, blue, light };

      Button(int x1, int y1, int x2, int y2, std::string caption, std::function<void()> action, Color color=grey, bool canToggle=false);
      void render();
      void mouseInputManagement(int mouseX, int mouseY, int *mouseState, int button);
      void setToggled(bool isToggled);

   private:
      Vector2 *edge;
      Color btnColor;
      State state;
      bool isToggled, canToggle;

      void onClick();
      void drawHover();
      void drawDefault();
      void drawClick();
      void drawEdge(float r, float g, float b);
};

#endif // BUTTON_H

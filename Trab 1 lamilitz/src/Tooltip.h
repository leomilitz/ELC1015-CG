/*
   Tooltip
   Autor: Leonardo Militz

   Implementação de uma tooltip para propósitos informativos - é usado no botão help. A
   tooltip pode ser visível ou invisível, e com hitbox circular ou retangular, garantindo
   sua versatilidade de uso. A classe é um UIComponent, mas não possui uma callback, já
   que sua unica função é exibir texto.
   --------------------------------------------------------------------------------------
   splitTooltipText: Faz o split do texto ao encontrar quebras de linha.
*/

#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <list>
#include <sstream>

#include "Vector2.h"
#include "UIComponent.h"

#define CHARSIZE 10
#define TEXT_OFFSET_Y 15
#define TEXT_OFFSET_X 5

class Tooltip: public UIComponent {
   public:
      Tooltip(int x1, int y1, int x2, int y2, std::string text, int width,
              int direction=1, bool visible=false, std::string btnText="");

      Tooltip(int x, int y, int radius, std::string text, int width,
              int direction=1, bool visible=false, std::string btnText="");

      void render();
      void inputManagement(int mouseX, int mouseY, int *mouseState);
   private:
      void drawTooltip();
      void splitTooltipText();

      Vector2 *posMouse;
      std::string text;
      std::list<std::string> splitText;
      bool visible, isHovering;
      int width, height, radius, direction;
};

#endif // TOOLTIP_H

/*
   Tooltip
   Autor: Leonardo Militz

   Implementa��o de uma tooltip para prop�sitos informativos - � usado no bot�o help. A
   tooltip pode ser vis�vel ou invis�vel, e com hitbox circular ou retangular, garantindo
   sua versatilidade de uso. A classe � um UIComponent, mas n�o possui uma callback, j�
   que sua unica fun��o � exibir texto.
   --------------------------------------------------------------------------------------
   splitTooltipText: Faz o split do texto ao encontrar quebras de linha.
*/

#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <vector>
#include <sstream>

#include "Vector2.h"
#include "UIComponent.h"

#define CHARSIZE 10
#define TEXT_OFFSET_Y 15
#define TEXT_OFFSET_X 5

class Tooltip: public UIComponent {
   public:
      Tooltip(int x1, int y1, int x2, int y2, std::string text, int width,
              int directionV=1, int directionH=1, bool visible=false, std::string btnText="");

      Tooltip(int x, int y, int radius, std::string text, int width,
              int directionV=1, int directionH=1, bool visible=false, std::string btnText="");

      void render();
      void inputManagement(int mouseX, int mouseY, int *mouseState);
   private:
      void drawTooltip();
      void splitTooltipText();

      Vector2 *posMouse;
      std::string text;
      std::vector<std::string> splitText;
      bool visible, isHovering;
      int width, height, radius, directionV, directionH;
};

#endif // TOOLTIP_H

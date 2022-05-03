/*
   Tooltip

   Implementação de uma tooltip para propósitos informativos - é usado no botão help. A
   tooltip pode ser visível ou invisível, e com hitbox circular ou retangular, garantindo
   sua versabilidade de uso.
   --------------------------------------------------------------------------------------
   splitTooltipText: Faz o split do texto ao encontrar quebras de linha.
*/

#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <string>
#include <list>
#include <sstream>

#include "Vector2.h"
#include "gl_canvas2d.h"

#define CHARSIZE 10
#define TEXT_OFFSET_Y 15
#define TEXT_OFFSET_X 5

class Tooltip {
   public:
      Tooltip(Vector2* p1, Vector2* p2, const char* text, int width, int height,
              int direction=1, bool visible=false, const char* btnText="");
      Tooltip(Vector2* center, int radius, const char* text, int width, int height,
              int direction=1, bool visible=false, const char* btnText="");

      void renderTooltip(Vector2* posMouse, bool visible);
   private:
      void drawTooltip(Vector2* posMouse);
      void splitTooltipText();

      Vector2 *p1, *p2;
      std::string text, btnText;
      std::list<std::string> splitText;
      bool visible;
      int width, height, radius, direction;
};

#endif // TOOLTIP_H

/*
   User Interface Manager
   Autor: Leonardo Militz

   Essa classe recebe todas as fun��es de render e input da main, e gerencia
   os componentes de interace de usu�rio (objetos UIComponent). Nessa classe s�o
   adicionados os bot�es, sliders, tooltip e background, e faz os seus tamanhos
   padr�o escalarem com o tamanho da tela. Essa classe tamb�m gerencia componentes visuais
   como o player e o cen�rio.
   ---------------------------------------------------------------------------
   - toggleCalculations: Ativa e desativa a visualiza��o dos c�lculos
*/

#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <list>
#include <string>

#include "Scenery/Background.h"
#include "Player/Player.h"
#include "UIComponent.h"
#include "Tooltip.h"
#include "Frames.h"

class UIManager {
   public:
      UIManager(int screenWidth, int screenHeight);
      void uiKeyboardInputManagement(int key, bool keyUp);
      void uiMouseInputManagement(int button, int state, int wheel, int direction, int x, int y);
      void uiRender();
      void uiCreate();

   private:
      void toggleCalculations();

      std::list<UIComponent*> components;
      Background* background;
      Player* player;

      int mouseX, mouseY, mouseState;
      int screenWidth, screenHeight;

      bool showCalcs;
      float speedMultiplier;

      Frames* frames;
};

#endif // UIMANAGER_H

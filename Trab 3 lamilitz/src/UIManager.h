/*
   User Interface Manager
   Autor: Leonardo Militz

   Essa classe recebe todas as funções de render e input da main, e gerencia
   os componentes de interace de usuário (objetos UIComponent). Nessa classe são
   adicionados os botões, sliders, tooltip e background, e faz os seus tamanhos
   padrão escalarem com o tamanho da tela. Essa classe também gerencia componentes visuais
   como o player e o cenário.
   ---------------------------------------------------------------------------
   - toggleCalculations: Ativa e desativa a visualização dos cálculos
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

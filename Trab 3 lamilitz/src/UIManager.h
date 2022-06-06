/*
   User Interface Manager
   Autor: Leonardo Militz

   Essa classe recebe todas as funções de render e input da main, e gerencia
   os componentes de interace de usuário (objetos UIComponent). Nessa classe são
   adicionados os botões, sliders, tooltip e background, e faz os seus tamanhos
   padrão escalarem com o tamanho da tela.
   ---------------------------------------------------------------------------
   - rememberComponents: Esse método é chamando quando acontece alguma mudança
   de imagem feita pelo usuário. É buscado o estado da nova imagem selecionada,
   e em seguida aplica essas mudanças no visual dos botões/sliders da UI.

   - resetComponents: Reseta o estado dos componentes para o padrão. É chamado
   quando alguma imagem é deletada.

   - getSlidersValues: Busca o valor dos sliders.
*/

#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <list>
#include <vector>

#include "Scenery/Background.h"
#include "Player/Player.h"
#include "UIComponent.h"
#include "Frames.h"

class UIManager {
   public:
      UIManager(int screenWidth, int screenHeight);
      void uiKeyboardInputManagement(int key, bool keyUp);
      void uiMouseInputManagement(int button, int state, int wheel, int direction, int x, int y);
      void uiRender();
      void uiCreate();

   private:
      std::list<UIComponent*> components;

      Background* background;
      Player* player;

      int mouseX, mouseY, mouseState;
      int screenWidth, screenHeight;
      int btnSmallWidth, btnMedWidth, btnBigWidth, btnSwitch, btnSpacingX,
          btnSpacingY, btnHeight;

      Frames* frames;
};

#endif // UIMANAGER_H

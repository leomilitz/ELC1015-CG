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

#include "ImageEditor.h"
#include "Tooltip.h"
#include "Button.h"
#include "Slider.h"

class UIManager {
   public:
      UIManager(int screenWidth, int screenHeight);
      void uiKeyboardInputManagement(int key, bool keyUp);
      void uiMouseInputManagement(int button, int state, int wheel, int direction, int x, int y);
      void uiRender();
      void uiCreate();

   private:
      void drawBackground();
      void rememberComponents();
      void resetComponents();
      int  getSlidersValues(std::string componentName);

      std::list<UIComponent*> components;
      ImageEditor* imgEditor;

      int mouseX, mouseY, mouseState;
      int screenWidth, screenHeight, collisionX, collisionY;
      int btnSmallWidth, btnMedWidth, btnBigWidth, btnSwitch, btnSpacingX,
          btnSpacingY, btnHeight, bgLineThickness;
};

#endif // UIMANAGER_H

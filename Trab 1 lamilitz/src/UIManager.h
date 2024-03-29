/*
   User Interface Manager
   Autor: Leonardo Militz

   Essa classe recebe todas as fun��es de render e input da main, e gerencia
   os componentes de interace de usu�rio (objetos UIComponent). Nessa classe s�o
   adicionados os bot�es, sliders, tooltip e background, e faz os seus tamanhos
   padr�o escalarem com o tamanho da tela.
   ---------------------------------------------------------------------------
   - rememberComponents: Esse m�todo � chamando quando acontece alguma mudan�a
   de imagem feita pelo usu�rio. � buscado o estado da nova imagem selecionada,
   e em seguida aplica essas mudan�as no visual dos bot�es/sliders da UI.

   - resetComponents: Reseta o estado dos componentes para o padr�o. � chamado
   quando alguma imagem � deletada.

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

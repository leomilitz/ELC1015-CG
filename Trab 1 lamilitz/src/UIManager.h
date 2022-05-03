/*
   User Interface Manager

   Essa classe recebe todas as fun��es de render e input da main, e integra as
   outras classes de gerenciamento de interface de usu�rio. Nessa classe s�o
   adicionados os bot�es, sliders, background, e faz os seus tamanhos padr�o
   escalarem com o tamanho da tela.
   ---------------------------------------------------------------------------
   - imageChangeControl: Esse m�todo recebe do image editor a flag que indica se
   houve alguma mudan�a de imagem pelo usu�rio ou n�o. Se a mudan�a existir,
   ser� buscado o estado da nova imagem selecionada, e em seguida aplica essas
   mudan�as no visual dos bot�es da UI.
*/

#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <vector>

#include "ImageEditor.h"
#include "ButtonManager.h"
#include "SliderManager.h"
#include "Tooltip.h"

class UIManager {
   public:
      UIManager(int screenWidth, int screenHeight);
      void uiKeyboardInputManagement(int key, bool keyUp);
      void uiMouseInputManagement(int button, int state, int wheel, int direction, int x, int y);
      void uiRender();
      void uiCreate();

   private:
      void drawBackground();
      void imageChangeControl();

      ImageEditor*   imgEditor;
      ButtonManager* btnManager;
      SliderManager* sldManager;
      Tooltip*       help;

      int mouseX, mouseY, mouseState;
      int screenWidth, screenHeight, collisionX, collisionY;
      int btnSmallWidth, btnMedWidth, btnBigWidth, btnSwitch, btnSpacingX,
          btnSpacingY, btnHeight, bgLineThickness;
      bool keyUp;
};

#endif // UIMANAGER_H

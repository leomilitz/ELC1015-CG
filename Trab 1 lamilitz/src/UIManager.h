/*
   User Interface Manager

   Essa classe recebe todas as funções de render e input da main, e integra as
   outras classes de gerenciamento de interface de usuário. Nessa classe são
   adicionados os botões, sliders, background, e faz os seus tamanhos padrão
   escalarem com o tamanho da tela.
   ---------------------------------------------------------------------------
   - imageChangeControl: Esse método recebe do image editor a flag que indica se
   houve alguma mudança de imagem pelo usuário ou não. Se a mudança existir,
   será buscado o estado da nova imagem selecionada, e em seguida aplica essas
   mudanças no visual dos botões da UI.
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

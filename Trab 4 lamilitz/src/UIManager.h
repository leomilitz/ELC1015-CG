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
#include <string>

#include "Curve.h"
#include "UIComponent.h"
#include "Frames.h"
#include "Button.h"
#include "Node.h"
#include "Vector3.h"
#include "SweepCurve.h"
#include "Tooltip.h"

#define NODE_MAX 6

class UIManager {
   public:
      UIManager(int screenWidth, int screenHeight);
      void uiKeyboardInputManagement(int key, bool keyUp);
      void uiMouseInputManagement(int button, int state, int wheel, int direction, int x, int y);
      void uiRender();
      void uiCreate();

   private:
      void showFps(float fps);
      void drawBackground();
      void addNode();
      void removeNode();
      void updateCurveCoordinates();

      std::list<UIComponent*> components;
      Curve* modelingCurve;
      SweepCurve* sweepCurve;
      Frames* frames;

      int mouseX, mouseY, mouseState;
      int screenWidth, screenHeight;
      int btnSmallWidth, btnMedWidth, btnBigWidth, btnSwitch, btnSpacingX,
          btnSpacingY, btnHeight, nodeRadius;
      int nodeCounter;
      std::string projMode, rotationMode, faceCount, pointCount;
};

#endif // UIMANAGER_H

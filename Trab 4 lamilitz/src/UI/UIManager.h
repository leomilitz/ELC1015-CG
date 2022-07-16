/**
 *  User Interface Manager
 *  Autor: Leonardo Militz
 *
 *  Essa classe recebe todas as fun��es de render e input da main, e gerencia
 *  os componentes de interace de usu�rio (objetos UIComponent). Nessa classe s�o
 *  adicionados os bot�es, sliders, tooltip, nodes, fps e background, e faz os seus tamanhos
 *  padr�o escalarem com o tamanho da tela.
 *  ---------------------------------------------------------------------------
 *  - addNode: Adiciona um nodo (ponto de controle) � curva de b�zier sendo renderizada na esquerda.
 *  - removeNode: Remove um nodo em que o mouse est� por cima.
 *  - updateCurveCoordinates: Altera as coordenadas da curva que est� sendo renderizada na esquerda
 *    ao mover um nodo, e atualiza a curva 3D na direita com base na altera��o.
 */

#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <list>
#include <vector>
#include <string>

#include "Figures/Curve.h"
#include "Figures/SweepCurve.h"
#include "Utils/Frames.h"
#include "Utils/Frames.h"
#include "UIComponent.h"
#include "Button.h"
#include "Node.h"
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
      std::string projMode, rotationMode, faceCount, pointCount,
                  yTranslation, sweepLapCount, helpTooltipText;
};

#endif // UIMANAGER_H

/*
   Classe para gerenciar a User Interface do programa. Seu functionamento básico envolve
   guardar todos objetos que abrangem a UI e loopar por eles, fazendo verificação
   de colisão e executando suas respectivas ações quando os objetos forem clicados.
*/

#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <vector>

#include "ImageEditor.h"
#include "ButtonManager.h"
#include "SliderManager.h"

class UIManager {
   public:
      UIManager(int screenWidth, int screenHeight);
      void uiKeyboardInputManagement(int key, bool keyUp);
      void uiMouseInputManagement(int button, int state, int wheel, int direction, int x, int y);
      void uiRender();
      void uiCreate();

   private:
      void drawBackground();

      ImageEditor* imgEditor;
      ButtonManager* btnManager;
      SliderManager* sldManager;
      int mouseButton, mouseWheel, mouseDirection, mouseX, mouseY,
          mouseState, screenHeight, screenWidth, key;
      bool keyUp;
      int collisionX, collisionY;
};

#endif // UIMANAGER_H

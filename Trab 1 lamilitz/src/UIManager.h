/*
   Classe para gerenciar a User Interface do programa. Seu functionamento b�sico envolve
   guardar todos objetos que abrangem a UI e loopar por eles, fazendo verifica��o
   de colis�o e executando suas respectivas a��es quando os objetos forem clicados.
*/

#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <vector>

#include "ImageEditor.h"
#include "ButtonManager.h"

class UIManager {
   public:
      UIManager(int screenWidth, int screenHeight);
      void uiKeyboardInputManagement(int key, bool keyUp);
      void uiMouseInputManagement(int button, int state, int wheel, int direction, int x, int y);
      void uiRender();
      void uiCreate();

   private:
      ImageEditor* imgEditor;
      ButtonManager* btnManager;

      int mouseButton, mouseWheel, mouseDirection, mouseX, mouseY;
      int mouseState, screenHeight, screenWidth;
      int key;
      bool keyUp;
};

#endif // UIMANAGER_H

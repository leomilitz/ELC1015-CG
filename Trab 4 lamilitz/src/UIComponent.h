/*
   UIComponent

   Classe genérica de um componente da interface de usuário. Ele estabelece
   as funções de renderização e de gerenciamento de input como virtuais para
   que as classes filhas possam se aproveitar do polimorfismo. Esse componente
   pode guardar uma função lambda como callback para ser chamada de forma
   genérica cada vez que um componente chama sua respectiva ação; essas funções
   callback são definidas de forma segura e reutilizável devido à biblioteca
   "functional" do C++, que permite que uma ação seja vinculada (binded) ao objeto.
   ------------------------------------------------------------------------
   Classes derivadas: Button, Tooltip, Slider
*/

#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include <functional>
#include <string>

#include "gl_canvas2d.h"
#include "Vector2.h"

#define CHARSIZE 10

class UIComponent
{
   public:
      enum UIComponentType { button, slider, tooltip, node, notype };

      UIComponent(int x1, int y1, int x2, int y2, std::string caption, std::function<void()> action);

      virtual ~UIComponent();
      virtual void render();
      virtual void mouseInputManagement(int mouseX, int mouseY, int *mouseState, int button);
      virtual void keyboardInputManagement(int key, bool keyUp);

      UIComponentType getType();
      std::string getCaption();

   protected:
      Vector2 *pos1, *pos2;
      std::string caption;
      std::function<void()> action;
      UIComponentType type;
};

#endif // UICOMPONENT_H

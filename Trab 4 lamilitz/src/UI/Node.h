/**
 *  Node
 *  Autor: Leonardo Militz
 *
 *  Visualização dos pontos de controle de uma curva de Bézier. Eles podem ser arrastados
 *  com o mouse e colidem com um limite imposto a partir das coordenadas (0,0).
 *  --------------------------------------------------------------------------------------
 */

#ifndef NODE_H
#define NODE_H

#include "UIComponent.h"

class Node: public UIComponent {
   public:
      enum NodeState { clicked, hovered, holding, standard };

      Node(float x, float y, int radius);
      virtual ~Node();

      void render();
      void mouseInputManagement(int mouseX, int mouseY, int* mouseState, int button);
      void setLimit(int x, int y);
      Vector2* getCoordinates();
      NodeState getState();

   private:
      void updatePosition(int x, int y);
      void nodeDragAround(Vector2* posMouse);

      bool isHolding;
      float radius;
      int outline;
      NodeState nodeState;
      Vector2* offset;
      Vector2 limit;
};

#endif // NODE_H

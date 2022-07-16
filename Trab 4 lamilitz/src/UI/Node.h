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
      void nodeDrawHoveringOutline();
      void nodeDrawSelectionOutline();
      void nodeDragAround(Vector2* posMouse);

      bool isHolding;
      float radius;
      int outline;
      NodeState nodeState;
      Vector2* offset;
      Vector2 limit;
};

#endif // NODE_H

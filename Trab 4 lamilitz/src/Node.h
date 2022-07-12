#ifndef NODE_H
#define NODE_H

#include "UIComponent.h"

class Node: public UIComponent {
   enum State  { clicked, hovered, holding, standard };

   public:
      Node(float x, float y, int radius);
      virtual ~Node();

      void render();
      void inputManagement(int mouseX, int mouseY, int* mouseState);

      void setLimit(int x, int y);
      Vector2* getCoordinates();

   private:
      void updatePosition(int x, int y);
      void nodeDrawHoveringOutline();
      void nodeDrawSelectionOutline();
      void nodeDragAround(Vector2* posMouse);

      bool isHolding, isFront, isCurrent;
      float radius;
      int outline;
      State nodeState;
      Vector2* offset;
      Vector2 limit;
};

#endif // NODE_H

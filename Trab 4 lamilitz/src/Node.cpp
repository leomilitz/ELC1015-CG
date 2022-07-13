#include "Node.h"

Node::Node(float x, float y, int radius):UIComponent(x, y, 0, 0, "", [](){}) {
   this->radius = radius;
   outline = 6;
   nodeState = standard;
   limit = Vector2(0,0);
   isCurrent = true;
   isFront = true;
   isHolding = false;
   offset = new Vector2(0,0);
   this->type = node;
}

Node::~Node(){ }

void Node::nodeDragAround(Vector2* posMouse) {
   if (isCurrent && isFront && isHolding) {
      Vector2 newPos = *posMouse - *offset;

      if (newPos + radius <= limit && newPos - radius >= Vector2(0,0)) {
         updatePosition(newPos.x, newPos.y);
         return;
      }

      if ((newPos.x + radius) > limit.x && (newPos.y + radius) < limit.y && (newPos.y - radius) > 0) {
         updatePosition(pos1->x, newPos.y);
         return;
      }

      if ((newPos.y + radius) > limit.y && (newPos.x + radius) < limit.x && (newPos.x - radius) > 0) {
         updatePosition(newPos.x, pos1->y);
         return;
      }

      if ((newPos.x - radius) < 0 && (newPos.y + radius) < limit.y && (newPos.y - radius) > 0) {
         updatePosition(pos1->x, newPos.y);
         return;
      }

      if ((newPos.y - radius) < 0 && (newPos.x + radius) < limit.x && (newPos.x - radius) > 0) {
         updatePosition(newPos.x, pos1->y);
         return;
      }
   }
}

void Node::inputManagement(int mouseX, int mouseY, int* mouseState) {
   Vector2* posMouse = new Vector2(mouseX, mouseY);
   nodeState = standard;

   if (pos1->distance(*posMouse) <= this->radius) {
      nodeState = hovered;

      if (*mouseState == 1) {
         isCurrent = true;
         isHolding = false;
         nodeState = clicked;
      }

      if (*mouseState == 0 && !isHolding) {
         isHolding = true;
         Vector2 _offset = *posMouse - *pos1;
         offset->x = _offset.x; offset->y = _offset.y;
         nodeState = holding;
      }
   }

   nodeDragAround(posMouse);
}

void Node::render() {
   CV::color(1,1,1);
   CV::circleFill(*pos1, radius, 20);
}

void Node::nodeDrawHoveringOutline() {
   for (int i = 0; i <= outline; i++) {
      float alpha = 1.0 - ((float) i / outline);
      CV::color(1.0, 0.2, 0.2, alpha);
      CV::circle(*pos1, radius + i, 20);
   }
}

void Node::updatePosition(int x, int y) {
   pos1->set(x, y);
}

void Node::setLimit(int x, int y) {
   limit = Vector2(x, y);
}

Vector2* Node::getCoordinates() { return pos1; }

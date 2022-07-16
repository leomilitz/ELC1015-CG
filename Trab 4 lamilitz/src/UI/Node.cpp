#include "Node.h"

Node::Node(float x, float y, int radius):UIComponent(x, y, 0, 0, "", [](){}) {
   this->radius = radius;
   outline = 6;
   nodeState = standard;
   limit = Vector2(0,0);
   isHolding = false;
   offset = new Vector2(0,0);
   this->type = node;
}

Node::~Node(){}

void Node::nodeDragAround(Vector2* posMouse) {
   if (isHolding) {
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

void Node::mouseInputManagement(int mouseX, int mouseY, int* mouseState, int button) {
   Vector2* posMouse = new Vector2(mouseX, mouseY);
   nodeState = standard;

   if (pos1->distance(*posMouse) <= this->radius) {
      nodeState = hovered;

      if (button == 0 && *mouseState == 0) {
         isHolding = true;
         Vector2 _offset = *posMouse - *pos1;
         offset->x = _offset.x; offset->y = _offset.y;
      }

      if (button == 0 && *mouseState == 1) {
         nodeState = holding;
         isHolding = false;
         nodeState = clicked;
      }
   }

   nodeDragAround(posMouse);
}

void Node::render() {
   CV::color(1,1,1);
   CV::circleFill(*pos1, radius, 20);
}

void Node::updatePosition(int x, int y) {
   pos1->set(x, y);
}

void Node::setLimit(int x, int y) {
   limit = Vector2(x, y);
}

Vector2* Node::getCoordinates() { return pos1; }
Node::NodeState Node::getState() { return nodeState; }

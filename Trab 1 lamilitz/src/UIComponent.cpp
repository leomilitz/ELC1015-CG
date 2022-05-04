#include "UIComponent.h"

UIComponent::UIComponent(int x1, int y1, int x2, int y2, std::string caption, std::function<void()> action) {
   pos1 = new Vector2(x1, y1);
   pos2 = new Vector2(x2, y2);
   this->caption = caption;
   this->action = std::bind(action);
   this->type = notype;
}

UIComponent::~UIComponent() { }

void UIComponent::render() {}
void UIComponent::inputManagement(int mouseX, int mouseY, int *mouseState) {}
std::string UIComponent::getCaption() { return caption; }
UIComponent::UIComponentType UIComponent::getType() { return type; }

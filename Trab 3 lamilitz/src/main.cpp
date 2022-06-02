#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include "gl_canvas2d.h"
#include "UIManager.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

UIManager *uiManager = NULL;

void render() {
   uiManager->uiRender();
}

void keyboard(int key) {
   uiManager->uiKeyboardInputManagement(key, false);
}

void keyboardUp(int key) {
   uiManager->uiKeyboardInputManagement(key, true);
}

void mouse(int button, int state, int wheel, int direction, int x, int y) {
   uiManager->uiMouseInputManagement(button, state, wheel, direction, x, y);
}

int main(void) {
   uiManager = new UIManager(SCREEN_WIDTH, SCREEN_HEIGHT);
   CV::init(SCREEN_WIDTH, SCREEN_HEIGHT, "LM - Bike Dude");
   CV::run();
   return 0;
}

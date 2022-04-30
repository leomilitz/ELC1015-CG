#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include "gl_canvas2d.h"
#include "UIManager.h"

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600

UIManager *uiManager = NULL;

//funcao chamada continuamente.
void render() {
   CV::clear(0,0,0);
   uiManager->uiRender();
}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key) {
   uiManager->uiKeyboardInputManagement(key, false);
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key) {
   uiManager->uiKeyboardInputManagement(key, true);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y) {
   uiManager->uiMouseInputManagement(button, state, wheel, direction, x, y);
}

int main(void) {
   uiManager = new UIManager(SCREEN_WIDTH, SCREEN_HEIGHT);
   CV::init(SCREEN_WIDTH, SCREEN_HEIGHT, "LM - Image Viewer");
   CV::run();
}

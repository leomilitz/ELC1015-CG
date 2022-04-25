#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include "gl_canvas2d.h"
#include "UIManager.h"

//variavel global para selecao do que sera exibido na canvas.
int screenWidth = 900, screenHeight = 600; //largura e altura inicial da tela . Alteram com o redimensionamento de tela.

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
   //printf("\nMouse (X: %d, Y: %d) state: %d", x, y, state);
}

int main(void) {
   uiManager = new UIManager(screenWidth, screenHeight);
   CV::init(&screenWidth, &screenHeight, "LM - Image Editor");
   CV::run();
}

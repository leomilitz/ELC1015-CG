/**
 *  SweepCurve
 *  Autor: Leonardo Militz
 *
 *  A classe SweepCurve recebe uma curva com par�metro, pega uma amostragem de seus pontos,
 *  e realiza um sweep rotacional ou transacional na figura gerada. Essa classe tamb�m �
 *  respons�vel por lidar internamente com intera��es com o mouse e teclado que influenciam
 *  em sua renderiza��o (como movimento da c�mera e rota��o).
 *  --------------------------------------------------------------------------------------
 *  - setCurve: Adiciona a curva de B�zier em que o sweep ser� baseado.
 *  - addPoints: Altera a quantidade de pontos retirados da amostragem, alterando o n�mero
 *    de linhas da matriz que guarda a mesh.
 *  - addSweepDivisor: Altera o "divisor do sweep", que na pr�tica muda o n�mero de faces da
 *    figura 3D gerada, por consequ�ncia, alterando a quantidade de colunas da mesh.
 *  - changePerspective: Altera a flag que decide se a figura ser� projetada em perspectiva
 *    ou em proje��o ortogonal.
 *  - changeRotationMode: Muda a forma em que ser� usada no sweep. A curva pode rotacionar em
 *    torno de seu pr�prio eixo ou em torno do eixo Y.
 *  - translateY: Translada o Y da figura para fazer um sweep translational. Na pr�tica permite
 *    a cria��o de figuras como molas.
 *  - addSweepLaps: Altera a quantidade de voltas que ser�o feitas na gera��o do sweep. Serve para
 *    "alongar" a mola.
 *  - getMidPoint: Pega o valor central da curva.
 */

#ifndef SWEEPCURVE_H
#define SWEEPCURVE_H

#include <vector>
#include <string>

#include "Curve.h"
#include "Utils/Vector3.h"

class SweepCurve {
   public:
      SweepCurve(Curve* curve, float x, float y, Vector2 cameraOffset, float axisOffset);
      virtual ~SweepCurve();

      void render(float fps);
      void mouseInputManagement(int button, int *state, int wheel, int direction, int mouseX, int mouseY, int div);
      void keyboardInputManagement(int key, bool keyUp);
      void setCurve(Curve* curve);
      std::string addPoints(float div);
      std::string addSweepDivisor(int div);
      std::string changePerspective();
      std::string changeRotationMode();
      std::string translateY(int value);
      std::string addSweepLaps(int value);

   private:
      enum RotationMode { selfRotate, translateAxis };

      Vector3 getMidPoint(std::vector<Vector3*> &points);
      Vector3 rotateX3D(Vector3 p);
      Vector3 rotateY3D(Vector3 p);
      Vector2 createProjection(Vector3 p);
      std::vector<std::vector<Vector3>> createMesh();
      std::vector<Vector3> calculateSweep(float angle, float translation);
      void drawWireFrame();

      Curve* curve;
      RotationMode rotationMode;
      Vector2 cameraOffset;
      std::vector<Vector3*> points;
      std::vector<std::vector<Vector3>> mesh;
      int sweepDivisor, sweepLaps;
      int mouseX, mouseY, mouseOffsetX, mouseOffsetY;
      float pointInc, thetaX, thetaY;
      float posX, posY, dist, axisOffset, translationValue;
      bool isOrtho, isHolding;
      float speed, fps, cameraSpeed;
};

#endif // SWEEPCURVE_H

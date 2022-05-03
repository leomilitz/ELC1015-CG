/*
   Image

   Classe que representa a imagem que o usu�rio est� interagindo. Ela � lida a partir de um
   bitmap (BGR) e guarda os dados da imagem em pixels (RGB). Podem existir multiplas imagens
   simult�neas na tela, e o usu�rio pode arrastar elas da forma que desejar.
   -----------------------------------------------------------------------------------------
   - imgRender: Renderiza a imagem pixel por pixel, e a partir de um switch controla os filtros
   e canais ativos na imagem. Tamb�m s�o salvos os dados necess�rios para o plot do histograma
   de cores.

   - resizeImage: Faz o scaling da imagem usando o algoritmo "nearest neighbor". Por quest�es de
   usabilidade, foi limitado o scaling m�nimo e m�ximo que o usu�rio pode dar na imagem para
   25% e 200% respectivamente.

   - flipHorizontal: Troca os pixels da metade direita com a metade esquerda, fazendo o "mirror"
   da imagem.

   - flipVertical:  Troca os pixels da metade de cima com a metade de baixo, fazendo a imagem
   ficar de cabe�a para baixo.

   - rotateImage: Faz a matriz transposta, e aplica um flip. O par�metro da fun��o define se
   a rota��o vai ser no sentido hor�rio ou anti hor�rio.

   - getImgState: Busca o estado da imagem e faz o controle da renderiza��o da outline com base
   em seu estado.

   - imgDragAround: Arrasta a imagem na tela com base na posi��o do mouse, e calcula o offset
   para que ela seja arrastada suavemente. Verifica colis�o com a UI.

   - modelData: L� os dados do bitmap, e salva em um vetor de Pixels. � feita a convers�o de BGR
   para RGB durante a leitura.

   - truncateColor: Ao fazer os c�lculos de brilho e contraste, esse m�todo garante que qualquer
   valor de cor que passe de 255 seja arredondado para 255, e qualquer valor que acabe ficando menor
   que zero seja arredondado para 0.
*/

#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <algorithm>

#include "Bmp.h"
#include "Vector2.h"
#include "gl_canvas2d.h"

#include <sstream>

typedef struct { int r, g, b; } Pixel;

class Image {
   public:
      enum State  { clicked, hovered, holding, standard };
      enum Filter { red, green, blue, luminance, inverted, bgr };

      Image(std::string &path, int idx, int x, int y);

      void imgRender();
      void resizeImage(double scale);
      void flipHorizontal();
      void flipVertical();
      void rotateImg(int side);
      bool checkCollision(int mouseX, int mouseY);

      bool isCurrentImg();
      State getImgState(int mouseX, int mouseY, int mouseState);
      std::vector<Filter> &getActiveFilters();
      int getIndex();
      int getBrightness();
      int getContrast();
      int getWidth();
      int getHeight();
      std::string& getImgName();
      std::vector<int>& getRGBValues(char color);

      void setIndex(int idx);
      void setImgFront(bool isFront);
      void setCurrent(bool isCurrent);
      void setFilter(Filter filter);
      void setBrightness(int value);
      void setContrast(int value);
      void setLimitX(int value);
      void setLimitY(int value);
      void setHolding(bool value);

   private:
      void imgDrawSelectionOutline();
      void imgDrawHoveringOutline();
      void imgDragAround(Vector2 *posMouse);
      void updatePosition(int x, int y);
      void modelData();
      int  truncateColor(int val);

      Bmp* bmp;
      std::string imgName;
      std::vector<Pixel*> data;
      std::vector<Filter> activeFilters;
      std::vector<int> redValues, greenValues, blueValues, luminanceValues;
      int outline, index, width, height, contrast, brightness, limitX, limitY;
      float scale;
      bool isHolding, isFront, isCurrent;
      Vector2 *pos1, *pos2, *offset;
      State imgState;
};

#endif // IMAGE_H

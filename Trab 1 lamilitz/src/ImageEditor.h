/*
   Image Editor

   Classe que representa o editor de imagens e faz o controle delas. O objetivo do image
   editor é aplicar os métodos de manipulação de imagem na imagem selecionada pelo usuário
   e também integrar o estado da imagem com o histograma de cores. Foram implementados
   controles que garantem que a imagem selecionada sempre estará na frente das outras,
   facilitando a visualização pelo usuário. Para isso, cada imagem tem um índice para
   auxiliar nesse tipo de controle.
   ---------------------------------------------------------------------------------------
   - checkClickedImagesPriority: Recebe as cordenadas do clique do usuário e busca qual imagem
   é a que está na frente das outras.

   - updateHistogram: Atualiza o histograma de cores a partir dos dados recebidos da imagem
   corrente. Fora a coleta e envio de dados para a classe do histograma, esse método
   tabém define o scaling que o eixo Y do histograma vai ter, verificando a cor mais
   recorrente na imagem.

   - listenToImageChange: é chamada pelo UIManager para saber se houve uma mudança de imagem
   selecionada pelo usuário.
*/

#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include <vector>

#include "Image.h"
#include "ColorHistogram.h"

#define MAX_IMAGES 4

class ImageEditor {
   public:
      ImageEditor(ColorHistogram *histogram);
      void addImage(int x, int y, std::string path);
      void inputManagement(int mouseX, int mouseY, int mouseState);
      int  checkClickedImagesPriority(float mouseX, float mouseY);
      void renderImages();
      void deleteImage();
      void resizeImage(double scale);
      void flipHorizontal();
      void flipVertical();
      void rotateImg(int side);
      void updateHistogram();
      bool listenToImageChange();

      std::vector<Image*> &getImages();
      std::string getImageName();
      int getCurrentImageIndex();

      void setBrightness(int value);
      void setContrast(int value);
      void setColorFilter(Image::Filter filter);
      void setCurrentImage(int idx);
   private:
      std::vector<Image*> images;
      int currentIndex;
      ColorHistogram *histogram;
      bool imgChanged;

      bool checkUserInputError();
};

#endif // IMAGEEDITOR_H

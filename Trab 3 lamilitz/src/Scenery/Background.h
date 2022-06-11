/*
   Background
   Autor: Leonardo Militz

   Gerenciador do background. Essa classe gera aleatoriamente todas as coordenadas e pro-
   priedades dos componentes visuais do background, e gera componentes constantemente
   formando um efeito parallax com base nas velocidades de cada componente.
   --------------------------------------------------------------------------------------
   - draw(Componente): Desenha o componente na tela e gerencia a quantidade de elementos dentro
     de seu vector.
   - add(Componente): Adiciona novos componentes no vetor com base nas coordenadas do ultimo
     elemento do vector.
   - getOutOfBonds(Componente): Verifica se o primeiro componente do vector está com suas
     coordenadas fora da tela. Se for o caso, ele é deletado para poder adicionar componentes
     novos pelo método "add".
   - showCalculations: Mostra as joints do background, por exemplo, os pontos que geram as
     curvas das montanhas.
*/

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../gl_canvas2d.h"
#include "../RandomUtils.h"

#include "Mountain.h"
#include "Building.h"
#include "Grass.h"

class Background {
   public:
      Background(int screenWidth, int screenHeight);
      void render(float fps);
      void showCalculations(bool showCalcs);
      void setSpeedMultiplier(float multiplier);

   private:
      void drawGround();
      void drawSky();
      void drawMountains();
      void drawBuildings();
      void drawGrass();
      void addMountain();
      void addBuilding();
      void addGrass();
      void createFirstMountain();
      void createFirstBuilding();
      void createFirstGrass();
      int getOutOfBoundsMountain();
      int getOutOfBoundsBuilding();
      int getOutOfBoundsGrass();

      int screenWidth, screenHeight;
      float mountainSpeed, buildingSpeed, grassSpeed, speedMultiplier, fps;
      bool showCalcs;

      std::vector<Mountain*> mountains;
      std::vector<Building*> buildings;
      std::vector<Grass*>  grass;

      RandomUtils ru;
};

#endif // BACKGROUND_H

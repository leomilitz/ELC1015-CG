//*********************************************************
//
// classe para fazer o carregamento de arquivos no formato BMP
// Autor: Cesar Tadeu Pozzer
//        pozzer@inf.ufsm.br
//  Versao 09/2010
//
//**********************************************************

#include "Bmp.h"

Bmp::Bmp(const char *fileName) {
   width = height = 0;
   data = NULL;

   if( fileName != NULL && strlen(fileName) > 0 )
      load(fileName);
}

void Bmp::load(const char *fileName) {
   FILE *fp = fopen(fileName, "rb");

   if( fp == NULL ) return;

   //le o HEADER componente a componente devido ao problema de alinhamento de bytes. Usando
   //o comando fread(header, sizeof(HEADER),1,fp) sao lidos 16 bytes ao inves de 14
   fread(&header.type,      sizeof(unsigned short int), 1, fp);
   fread(&header.size,      sizeof(unsigned int),       1, fp);
   fread(&header.reserved1, sizeof(unsigned short int), 1, fp);
   fread(&header.reserved2, sizeof(unsigned short int), 1, fp);
   fread(&header.offset,    sizeof(unsigned int),       1, fp);

   //le o INFOHEADER componente a componente devido ao problema de alinhamento de bytes
   fread(&info.size,        sizeof(unsigned int),       1, fp);
   fread(&info.width,       sizeof(int),                1, fp);
   fread(&info.height,      sizeof(int),                1, fp);
   fread(&info.planes,      sizeof(unsigned short int), 1, fp);
   fread(&info.bits,        sizeof(unsigned short int), 1, fp);
   fread(&info.compression, sizeof(unsigned int),       1, fp);
   fread(&info.imagesize,   sizeof(unsigned int),       1, fp);
   fread(&info.xresolution, sizeof(int),                1, fp);
   fread(&info.yresolution, sizeof(int),                1, fp);
   fread(&info.ncolours,    sizeof(unsigned int),       1, fp);
   fread(&info.impcolours,  sizeof(unsigned int),       1, fp);

   width  = info.width;
   height = info.height;
   bits   = info.bits;
   bytesPerLine =(3 * (width + 1) / 4) * 4;
   imagesize    = bytesPerLine*height;

   if( header.type != 19778 )        return;
   if( width*height*3 != imagesize ) return;
   if( info.compression != 0 )       return;
   if( bits != 24 )                  return;
   if( info.planes != 1 )            return;

   data = new unsigned char[imagesize];
   fseek(fp, header.offset, SEEK_SET);
   fread(data, sizeof(unsigned char), imagesize, fp);
   fclose(fp);
}

uchar* Bmp::getImage() { return data; }
int Bmp::getWidth(void) { return width; }
int Bmp::getHeight(void) { return height; }

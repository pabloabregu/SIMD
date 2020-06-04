#ifndef FILTROS_H
#define FILTROS_H

#include "bmp.h"

typedef struct tagFILTRO {

	float RR, RG, RB;
	float GR, GG, GB;
	float BR, BG, BB;
} FILTRO;

FILTRO SEPIA;

void filtro (BMPDATA*, FILTRO);
void blancoYNegro (BMPDATA*);
void aclarar(BMPDATA*,int);
void medianFilter (BMPDATA*);
void multiplyBlend(BMPDATA *bmpOne, BMPDATA *bmpTwo);
void blend(BMPDATA*,BMPDATA*);
void blendSIMD(BMPDATA*,BMPDATA*);
void negativo(BMPDATA *bmpData);
void escalaDeGrises(BMPDATA *bmpData);
int calcularMedia(int r, int g, int b);
int cantPixels (BMPDATA*);
unsigned char mediana (unsigned char*, int);
#endif

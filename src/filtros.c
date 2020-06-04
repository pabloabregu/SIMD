#include "filtros.h"
#include <stdio.h>
#include <string.h>
// intel simd
#if defined(__SSE2__)
#include <emmintrin.h>
#endif
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

extern int asmMultiply(int a, int b);
extern unsigned char mulBlend(unsigned char a, unsigned char b);
extern unsigned char *mulSIMD(unsigned char *a, unsigned char *b);
extern unsigned char divide(unsigned char a);

//FILTRO SEPIA = {
//	.393, .760, .189,
//	.349, .686, .168,
//	.272, .534, .131
//};

typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
} Pixel;

typedef Pixel t_Window[9];

/******************************************************************************/

void filtro(BMPDATA *bmpData, FILTRO filtro)
{

	for (int i = 0; i < cantPixels(bmpData); i++)
	{

		unsigned char r = bmpData->red[i];
		unsigned char g = bmpData->green[i];
		unsigned char b = bmpData->blue[i];
		bmpData->red[i] = min(r * filtro.RR + g * filtro.RG + b * filtro.RB, 255);
		bmpData->green[i] = min(r * filtro.GR + g * filtro.GG + b * filtro.GB, 255);
		bmpData->blue[i] = min(r * filtro.BR + g * filtro.BG + b * filtro.BB, 255);
	}
}

/******************************************************************************/

void blancoYNegro(BMPDATA *bmpData)
{

	for (int i = 0; i < cantPixels(bmpData); i++)
	{

		unsigned char y = bmpData->red[i] * 0.11448f + bmpData->green[i] * 0.58661f + bmpData->blue[i] * 0.29891f;
		bmpData->red[i] = y;
		bmpData->green[i] = y;
		bmpData->blue[i] = y;
	}
}

void aclarar(BMPDATA *bmpData, int n)
{

	for (int i = 0; i < cantPixels(bmpData); i++)
	{
		unsigned char r = bmpData->red[i];
		unsigned char g = bmpData->green[i];
		unsigned char b = bmpData->blue[i];
		bmpData->red[i] = min(r + n, 255);
		bmpData->green[i] = min(g + n, 255);
		bmpData->blue[i] = min(b + n, 255);
	}
}

void medianFilter(BMPDATA *bmpData)
{
	long N = bmpData->infoHeader.biWidth;
	long M = bmpData->infoHeader.biHeight;

	//   Recorremos los pixeles
	for (int m = 1; m < M - 1; ++m)
	{ // Alto
		for (int n = 1; n < N - 1; ++n)
		{ // Ancho
			int k = 0;
			t_Window window; //Inicializamos ventana de pixeles 3x3 ;
			for (int j = m - 1; j < m + 2; ++j)
			{
				for (int i = n - 1; i < n + 2; ++i)
				{
					window[k].b = bmpData->blue[j * N + i];	 //
					window[k].g = bmpData->green[j * N + i]; //  Carga los pixeles en la ventana 3x3
					window[k].r = bmpData->red[j * N + i];	 //
					k++;
					//   Ordenamos los elementos  azules
					for (int j = 0; j < 5; ++j)
					{
						int min = j;
						for (int l = j + 1; l < 9; ++l)
						{
							int aux, aux2;
							aux = (int)window[l].b;
							aux2 = (int)window[min].b;
							if (aux < aux2)
							{
								min = l;
							}
						}
						const unsigned char temp = window[j].b;
						window[j].b = window[min].b;
						window[min].b = temp;
					}
					//   Modificamos la componente azul del pixel de la imagen
					bmpData->blue[(m - 1) * N + (n - 1)] = window[4].b;
					//   Ordenamos los elementos verdes
					for (int j = 0; j < 5; ++j)
					{
						int min = j;
						for (int l = j + 1; l < 9; ++l)
						{
							int aux, aux2;
							aux = (int)window[l].g;
							aux2 = (int)window[min].g;
							if (aux < aux2)
							{
								min = l;
							}
						}
						const unsigned char temp = window[j].g;
						window[j].g = window[min].g;
						window[min].g = temp;
					}
					//   Modificamos la componente verde del pixel de la imagen
					bmpData->green[(m - 1) * N + (n - 1)] = window[4].g;
					//   Ordenamos los elementos rojos
					for (int j = 0; j < 5; ++j)
					{
						int min = j;
						for (int l = j + 1; l < 9; ++l)
						{
							int aux, aux2;
							aux = (int)window[l].r;
							aux2 = (int)window[min].r;
							if (aux < aux2)
							{
								min = l;
							}
						}
						const unsigned char temp = window[j].r;
						window[j].r = window[min].r;
						window[min].r = temp;
					}
					//   Modificamos la componente roja del pixel de la imagen
					bmpData->red[(m - 1) * N + (n - 1)] = window[4].r;
				}
			}
		}
	}
}

void multiplyBlend(BMPDATA *bmpOne, BMPDATA *bmpTwo)
{
	printf("ALTO = %i \n ANCHO = %i", bmpOne->infoHeader.biHeight, bmpOne->infoHeader.biWidth);
	for (int i = 0; i < cantPixels(bmpOne); i++)
	{
		bmpOne->red[i] = asmMultiply(bmpTwo->red[i], bmpOne->red[i]);
		bmpOne->green[i] = asmMultiply(bmpTwo->green[i], bmpOne->green[i]);
		bmpOne->blue[i] = asmMultiply(bmpTwo->blue[i], bmpOne->blue[i]);
	}
}

void blend(BMPDATA *bmpData, BMPDATA *bmpData2)
{
	// unsigned char componente;
	// unsigned char componente2;
	// unsigned char result;
	// 	for (int i=0; i<cantPixels(bmpData); i++) {
	// 		componente = bmpData->red[i];
	// 		componente2 = bmpData2->red[i];
	// 		result = mulBlend(componente,componente2);
	// 		bmpData->red[i] =  result;

	// 		componente = bmpData->green[i];
	// 		componente2 = bmpData2->green[i];
	// 		result = mulBlend(componente,componente2);
	// 		bmpData->green[i] =result;

	// 	    componente = bmpData->blue[i];
	// 		componente2= bmpData2->blue[i];
	// 		result = mulBlend(componente,componente2);
	// 		bmpData->blue[i] = result;
	// 	}
}

void blendSIMD(BMPDATA *bmpData, BMPDATA *bmpData2)
{
	unsigned char v[3] = {0, 0, 0};
	unsigned char v2[3] = {0, 0, 0};
	unsigned char r, g, b;

	for (int i = 0; i < cantPixels(bmpData); i++)
	{
		v[0] = bmpData->blue[i];
		v[1] = bmpData->green[i];
		v[2] = bmpData->red[i];

		v2[0] = bmpData2->blue[i];
		v2[1] = bmpData2->green[i];
		v2[2] = bmpData2->red[i];

		mulSIMD(v, v2);
		r = v[0];
		g = v[1];
		b = v[2];
		bmpData->blue[i] = b;
		bmpData->green[i] = g;
		bmpData->red[i] = r;
	}
}

void negativo(BMPDATA *bmpData)
{
	for (int i = 0; i < cantPixels(bmpData); i++)
	{
		bmpData->red[i] = 255 - bmpData->red[i];
		bmpData->green[i] = 255 - bmpData->green[i];
		bmpData->blue[i] = 255 - bmpData->blue[i];
	}
}

void escalaDeGrises(BMPDATA *bmpData)
{
	for (int i = 0; i < cantPixels(bmpData); i++)
	{
		int media = calcularMedia(bmpData->red[i], bmpData->green[i], bmpData->blue[i]);
		bmpData->red[i] = media;
		bmpData->green[i] = media;
		bmpData->blue[i] = media;
	}
}

int calcularMedia(int r, int g, int b)
{
	int aux = r + g + b;
	return aux / 3;
}
/******************************************************************************/

unsigned char mediana(unsigned char *histo, int imediana)
{

	int k, aux = 0;
	for (k = 0; k < 255 && aux <= imediana; k++)
		aux += histo[k];

	return k;
}

/******************************************************************************/

int cantPixels(BMPDATA *bmpData)
{

	return bmpData->infoHeader.biWidth * bmpData->infoHeader.biHeight;
}

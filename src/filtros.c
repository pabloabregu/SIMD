#include "filtros.h"
#include <stdio.h>

// intel simd
#if defined(__SSE2__)
#include <emmintrin.h>
#endif

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

FILTRO SEPIA = { 
	.393, .760, .189,
	.349, .686, .168,
	.272, .534, .131
};

/******************************************************************************/

void filtro (BMPDATA *bmpData, FILTRO filtro) {

	for (int i=0; i<cantPixels(bmpData); i++) {

		unsigned char r = bmpData->red[i];
		unsigned char g = bmpData->green[i];
		unsigned char b = bmpData->blue[i];
		bmpData->red[i]   = min (r * filtro.RR + g * filtro.RG + b * filtro.RB, 255);
		bmpData->green[i] = min (r * filtro.GR + g * filtro.GG + b * filtro.GB, 255);
		bmpData->blue[i]  = min (r * filtro.BR + g * filtro.BG + b * filtro.BB, 255);
	}
}

/******************************************************************************/

void blancoYNegro (BMPDATA *bmpData) {
	
	for (int i=0; i<cantPixels(bmpData); i++) {
	
		unsigned char y = bmpData->red[i] * 0.11448f + bmpData->green[i] * 0.58661f + bmpData->blue[i] * 0.29891f;
		bmpData->red[i]   = y;
		bmpData->green[i] = y;
		bmpData->blue[i]  = y;
	}	
}

/******************************************************************************/

unsigned char mediana (unsigned char *histo, int imediana) {

	int k, aux=0;
	for (k=0; k<255 && aux<=imediana; k++)
		aux += histo[k];

	return k;
}

/******************************************************************************/

int cantPixels(BMPDATA *bmpData) {

	return bmpData->infoHeader.biWidth * bmpData->infoHeader.biHeight;
}
	

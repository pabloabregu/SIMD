#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "lectorBmp.h"
#include "filtros.h"


/*
 * Funciones en asembler
 */
//extern void blendAsm (char *, char *, char *, int, int, int, int);


// DOC_HELP

/******************************************************************************/


int main (int argc, char* argv[]) {
	printf("Organización del Computador 2.\nTrabajo Práctico Nro. 2\nPrograma para procesamiento de imágenes BMP.\n");
	int resolucion = 1080;
	BMPDATA bmpData;
	BMPDATA bmpData2;
	int i;

	/*printf("Ejecutando con parametros: ");
	for (i=1 ; i<argc; i++){
		printf("%s ", argv[i]);
	}*/

	// carga el archivo bmp
	if (loadBmpFile ("blend.bmp", &bmpData) != 0) {

		printf ("Error al leer el archivo %s\n\n", "blend.bmp");
		return 1;
	}

	if (loadBmpFile ("blend2.bmp", &bmpData2) != 0) {

		printf ("Error al leer el archivo %s\n\n", "blend2.bmp");
		return 1;
	}

	clock_t start, end;
	
	// comienza a medir el tiempo
	start = clock();
//Llamadas a filtros

	//blancoYNegro (&bmpData);
	//aclarar(&bmpData , 50);
//	medianFilter(&bmpData);
//	blend(&bmpData,&bmpData2);
	multiplyBlend(&bmpData,&bmpData2);
//	blendSIMD(&bmpData,&bmpData2);
//negativo(&bmpData);
//escalaDeGrises(&bmpData);

	end = clock();
	FILE *out = fopen("results.csv", "a");  
	int tiempo = end-start;
	fprintf(out, "%d %s %d", resolucion, " tiempo: ", tiempo );
  	fclose(out); 

	// imprime tiempo
	
	printf("\nTiempo de proceso: %ld ticks.\n\n", end-start);

	if (saveBmpFile ("blend_3.bmp", &bmpData) != 0)
		printf("Error al grabar el archivo!");
	
	// libera memoria
	limpiarBmpData(&bmpData);
	limpiarBmpData(&bmpData2);
	return 0;
}

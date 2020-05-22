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



extern int asmPrint
(char * msg, int lenght);

int asm_Print(char * msg){
  return asmPrint(msg,strlen(msg));
}
/******************************************************************************/


int main (int argc, char* argv[]) {
	asm_Print("Organización del Computador 2.\nTrabajo Práctico Nro. 2\nPrograma para procesamiento de imágenes BMP.\n");
	int resolucion = 1080;
	BMPDATA bmpData;
	int i;

	/*printf("Ejecutando con parametros: ");
	for (i=1 ; i<argc; i++){
		printf("%s ", argv[i]);
	}*/

	// carga el archivo bmp
	if (loadBmpFile ("lena.bmp", &bmpData) != 0) {

		printf ("Error al leer el archivo %s\n\n", "lena.bmp");
		return 1;
	}

	clock_t start, end;
	
	// comienza a medir el tiempo
	start = clock();

	// tonos de grises
	blancoYNegro (&bmpData);

	end = clock();
	FILE *out = fopen("results.csv", "a");  
	int tiempo = end-start;
	fprintf(out, "%d %s %d", resolucion, " tiempo: ", tiempo );
  	fclose(out); 

	// imprime tiempo
	
	printf("\nTiempo de proceso: %ld ticks.\n\n", end-start);

	if (saveBmpFile ("lena.bmp", &bmpData) != 0)
		asm_Print("Error al grabar el archivo!");
	
	// libera memoria
	limpiarBmpData(&bmpData);
	return 0;
}

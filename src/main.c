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
typedef enum
{
	false,
	true
} bool;

int main(int argc, char *argv[])
{
	printf("Organización del Computador 2.\nTrabajo Práctico Nro. 2\nPrograma para procesamiento de imágenes BMP.\n");
	int resolucion = 1080;
	BMPDATA bmpData;
	BMPDATA bmpData2;
	BMPDATA bmpData3;
	BMPDATA bmpData4;
	int i;

	// carga el archivo bmp
	if (loadBmpFile("images/lena.bmp", &bmpData) != 0)
	{
		printf("Error al leer el archivo %s\n\n", "lena.bmp");
		return 1;
	}
	if (loadBmpFile("images/lena_corrompido.bmp", &bmpData2) != 0)
	{
		printf("Error al leer el archivo %s\n\n", "lena_corrompido.bmp");
		return 1;
	}
	if (loadBmpFile("images/blend.bmp", &bmpData3) != 0)
	{
		printf("Error al leer el archivo %s\n\n", "blend.bmp");
		return 1;
	}
	if (loadBmpFile("images/blend2.bmp", &bmpData4) != 0)
	{
		printf("Error al leer el archivo %s\n\n", "blend2.bmp");
		return 1;
	}

	clock_t start, end;

	// comienza a medir el tiempo
	start = clock();

	bool salida = false;
	int respuesta;

	//------------------------INICIO------------------------
	while (!salida)
	{
		printf("\n######## Filtros ########\n\n");
		printf("1- Blanco y negro\n");
		printf("2- Aclarar\n");
		printf("3- Median Filter\n");
		printf("4- Blend\n");
		printf("5- BlendSIMD\n");
		printf("6- Negativo\n");
		printf("7- Escala de Grises\n");
		printf("0- Salir\n");

		printf("\n>> ");
		scanf("%d", &respuesta);
		fflush(stdin);

		switch (respuesta)
		{
		case (1):
			system("clear");
			blancoYNegro(&bmpData);
			end = clock();
			FILE *out = fopen("result.csv", "a");
			int tiempo = end - start;
			fprintf(out, "\nBlanco y Negro: %d %s %d", resolucion, " tiempo: ", tiempo);
			fclose(out);

			// imprime tiempo

			printf("\nTiempo de proceso: %ld ticks.\n\n", end - start);

			if (saveBmpFile("resultadoBlancoNegro.bmp", &bmpData) != 0)
				printf("Error al grabar el archivo!");

			// libera memoria
			limpiarBmpData(&bmpData);
			system("eog resultadoBlancoNegro.bmp");
			return 0;
			break;

		case (2):
			system("clear");
			aclarar(&bmpData, 50);
			end = clock();
			FILE *out1 = fopen("result.csv", "a");
			int tiempo1 = end - start;
			fprintf(out1, "\nAclarar: %d %s %d", resolucion, " tiempo: ", tiempo1);
			fclose(out1);

			// imprime tiempo

			printf("\nTiempo de proceso: %ld ticks.\n\n", end - start);

			if (saveBmpFile("resultadoAclarar.bmp", &bmpData) != 0)
				printf("Error al grabar el archivo!");

			// libera memoria
			limpiarBmpData(&bmpData);
			system("eog resultadoAclarar.bmp");
			return 0;
			break;

		case (3):
			system("clear");
			medianFilter(&bmpData2);
			end = clock();
			FILE *out2 = fopen("result.csv", "a");
			int tiempo2 = end - start;
			fprintf(out2, "\nMedian Filter: %d %s %d", resolucion, " tiempo: ", tiempo2);
			fclose(out2);

			// imprime tiempo

			printf("\nTiempo de proceso: %ld ticks.\n\n", end - start);

			if (saveBmpFile("resultadoMedianFilter.bmp", &bmpData2) != 0)
				printf("Error al grabar el archivo!");

			// libera memoria
			limpiarBmpData(&bmpData2);
			system("eog resultadoMedianFilter.bmp");
			return 0;

			break;

		case (4):
			system("clear");
			multiplyBlend(&bmpData3, &bmpData4);
			end = clock();
			FILE *out3 = fopen("result.csv", "a");
			int tiempo3 = end - start;
			fprintf(out3, "\n Blend: %d %s %d", resolucion, " tiempo: ", tiempo3);
			fclose(out3);

			// imprime tiempo

			printf("\nTiempo de proceso: %ld ticks.\n\n", end - start);

			if (saveBmpFile("resultadoBlend.bmp", &bmpData3) != 0)
				printf("Error al grabar el archivo!");

			// libera memoria
			limpiarBmpData(&bmpData3);
			limpiarBmpData(&bmpData4);
			system("eog resultadoBlend.bmp");
			return 0;

			break;

		case (5):
			system("clear");	
			//blendSIMD(&bmpData3,&bmpData4);
			printf("-------------.\n");
			printf("No disponible.\n");
			printf("-------------.\n");
			return 0;
			break;

		case (6):
			system("clear");
			negativo(&bmpData3);
			end = clock();
			FILE *out4 = fopen("result.csv", "a");
			int tiempo4 = end - start;
			fprintf(out4, "\nNegativo: %d %s %d", resolucion, " tiempo: ", tiempo4);
			fclose(out4);

			// imprime tiempo

			printf("\nTiempo de proceso: %ld ticks.\n\n", end - start);

			if (saveBmpFile("resultadoNegativo.bmp", &bmpData3) != 0)
				printf("Error al grabar el archivo!");

			// libera memoria
			limpiarBmpData(&bmpData3);
			system("eog resultadoNegativo.bmp");
			return 0;

			break;
		case (7):
			system("clear");
			escalaDeGrises(&bmpData3);
			end = clock();
			FILE *out5 = fopen("result.csv", "a");
			int tiempo5 = end - start;
			fprintf(out5, "\n Escala de Gris: %d %s %d", resolucion, " tiempo: ", tiempo5);
			fclose(out5);

			// imprime tiempo

			printf("\nTiempo de proceso: %ld ticks.\n\n", end - start);

			if (saveBmpFile("resultadoEscalaDeGrises.bmp", &bmpData3) != 0)
				printf("Error al grabar el archivo!");

			// libera memoria
			limpiarBmpData(&bmpData3);
			system("eog resultadoEscalaDeGrises.bmp");
			return 0;
			break;

		case (0):
			salida = true;
			break;

		default:
			system("clear");
			printf("No ingresaste una opcion correcta.\n");
			system("pause");
			system("clear");
			break;
		}
	}
}

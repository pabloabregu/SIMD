#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"

/* la función devuelve 0 si la lectura fue exitosa otro valor en caso contrario
 *
 * en la función se pide memoria para los canales RGB
 * 
 * para liberar la memoria llamar a LimpiarBmpData(BMPDATA*)
 */

int loadBmpFile(char *filename, BMPDATA *bmpData) {

	FILE *filePtr;
	unsigned char *buffer;  //buffer de lectura

	//abre el archivo en modo binario
	filePtr = fopen(filename,"rb");
	if (filePtr == NULL)
		return 1;

	//lee el header del fichero
	fread(&bmpData->fileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

	//verifica si es un archivo bmp
	if (bmpData->fileHeader.bfType != 0x4D42) {

		fclose(filePtr);
		return 1;
	}

	//lee el infoHeader del bitmap
	fread(&bmpData->infoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	//mueve el puntero al comienzo de los datos del bitmap
	const int offset = bmpData->fileHeader.bOffBits;
	fseek(filePtr, offset, SEEK_SET);

	//localiza memoria para los datos del bitmap
	const int biSize = bmpData->infoHeader.biSizeImage;
	buffer = (unsigned char*)malloc(biSize);

	//lee los datos del bitmap al buffer
	fread(buffer, biSize, 1, filePtr);

	//cantidad de pixeles de la imagen
	const int cantPixels = biSize / 3;
	
	//reservar memoria para canales de colores
	bmpData->red   = (unsigned char*)malloc(cantPixels);
	bmpData->green = (unsigned char*)malloc(cantPixels);
	bmpData->blue  = (unsigned char*)malloc(cantPixels);

	//pasa la información del bitmap a los canales de colores
	for (int i=0; i<cantPixels; i++) {

		bmpData->red[i]   = buffer[i*3+2];
		bmpData->green[i] = buffer[i*3+1];
		bmpData->blue[i]  = buffer[i*3+0];
	}

	//limpia memoria del buffer
	free(buffer);

	fclose(filePtr);

	return 0;
}

void limpiarBmpData(BMPDATA *bmpData) {

	//libera datos de los canales de colores
	free(bmpData->red);	
	free(bmpData->green);
	free(bmpData->blue);

	return;
}

int saveBmpFile(char *filename, BMPDATA * bmpData) {

	FILE *f;

	f = fopen (filename, "wb");

	//offset hasta los datos del bitmap
	bmpData->fileHeader.bOffBits = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);

	//tamaño del archivo
	const int tam = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmpData->infoHeader.biSizeImage;
	bmpData->fileHeader.bfSize = tam;

	//tamaño de la info del bitmap
	bmpData->infoHeader.biSize = sizeof(BITMAPINFOHEADER);

	//escribe la cabecera del fichero
	fwrite (&bmpData->fileHeader, 1, sizeof(BITMAPFILEHEADER), f);

	//escribe la cabecera de los datos del bitmap
	fwrite (&bmpData->infoHeader, 1, sizeof(BITMAPINFOHEADER), f);

	const int cantPixels = bmpData->infoHeader.biSizeImage / 3;
	
	for (int i=0; i<cantPixels; i++) {

		fwrite (&bmpData->blue[i],  1, 1, f);
		fwrite (&bmpData->green[i], 1, 1, f);
		fwrite (&bmpData->red[i],   1, 1, f);
	}

	fclose(f);
	return 0;
}

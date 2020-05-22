#ifndef LECTORBMP_H
#define LECTORBMP_H

#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"

int loadBmpFile(char*, BMPDATA*);
void limpiarBmpData(BMPDATA*);
int saveBmpFile(char*, BMPDATA*);

#endif

#ifndef PRINT_H
#define PRINT_H

#include <errno.h>
#include <stdio.h>

#include "parse.h"
#include "tables.h"

void CatFile(FILE *file, param par, const char *table[static 256]);
void Cat(int argc, char *argv[], param par, const char *table[static 256]);

#endif
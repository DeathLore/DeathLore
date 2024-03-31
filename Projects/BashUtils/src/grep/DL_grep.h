#ifndef DL_GREP_H
#define DL_GREP_H

#include "includes.h"

int initTemplate(char **str, char *optarg);
void addTemplate(char **str, char *optarg);
void *increaseStr(void *str, int size);

#endif
#ifndef PRINT_H
#define PRINT_H

#include "includes.h"
#include "parse.h"

int DL_grep(char *path, param par, char *template);
void extraInfo(param par, char *path);
void mainInfo(char *line, param *par, char *template, char *path);
void paramO(regex_t regex, char *line, param *par, char const *const path);

#endif
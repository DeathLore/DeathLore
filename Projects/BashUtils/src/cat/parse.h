#ifndef PARSE_H
#define PARSE_H

#include <getopt.h>

typedef struct {
  int b;
  int e;
  int E;
  int n;
  int s;
  int t;
  int T;
  int v;
} param;

int parse_params(int argc, char **argv, char *short_options,
                 struct option long_options[], param *par);

#endif
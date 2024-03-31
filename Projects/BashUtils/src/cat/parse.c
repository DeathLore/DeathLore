#include "parse.h"

#include <getopt.h>

int parse_params(int argc, char **argv, char *short_options,
                 struct option long_options[], param *par) {
  int res;
  int error = 0;
  int idx = 0;

  while ((res = getopt_long(argc, argv, short_options, long_options, &idx)) !=
         -1) {
    switch (res) {
      case 'b':
        par->b = 1;
        break;

      case 'e':
        par->e = 1;
        par->v = 1;
        break;

      case 'E':
        par->e = 1;
        break;

      case 'n':
        par->n = 1;
        break;

      case 's':
        par->s = 1;
        break;

      case 't':
        par->t = 1;
        par->v = 1;
        break;

      case 'T':
        par->t = 1;
        break;

      case 'v':
        par->v = 1;
        break;

      case '?':
        error = 1;
        break;

      default:
        error = 1;
        break;
    }
  }

  return error ? 1 : 0;
}
#include "DL_grep.h"

#include "includes.h"
#include "parse.h"
#include "print.h"

int main(int argc, char **argv) {
  int error = 0;
  if (argc > 1) {
    char *template = NULL;
    param par = {0};  // parametrs
    char options[] = "e:ivclnhsf:o";
    int retval[2] = {0, 0};  // 1 - error; 2 - optind
    parse_params(argc, argv, &par, &template, options, retval);
    for (int x = retval[1]; x < argc; x += 1) {
      if (retval[0] == 0) retval[0] = DL_grep(argv[x], par, template);
      if (retval[0] == 1) {
        error = 1;
        break;
      }
    }

    if (template != NULL) free(template);
  } else
    error = 1;

  if (error) printf("Error!\n");

  return 0;
}

int initTemplate(char **str, char *optarg) {
  *str = calloc(strlen(optarg) + 1, 1);
  if (*str) strcpy(*str, optarg);
  return str ? 1 : 0;
}

void addTemplate(char **str, char *optarg) {
  *str = increaseStr(*str, strlen(*str) + strlen(optarg) + 2);
  if (*str) strcat(strcat(*str, "|"), optarg);
}

void *increaseStr(void *str, int size) {
  char *buf = realloc(str, size);
  return buf;
}
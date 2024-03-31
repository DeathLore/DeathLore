#include <getopt.h>
#include <stdio.h>

#include "parse.h"
#include "print.h"
#include "tables.h"

int main(int argc, char **argv) {
  param par = {0};
  const char *table[256];

  char *short_options = "beEnstTv";
  struct option long_options[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                  {"number", no_argument, NULL, 'n'},
                                  {"squeeze-blank", no_argument, NULL, 's'}};

  int error = parse_params(argc, argv, short_options, long_options, &par);

  if (error)
    return 1;
  else {
    CatSetTable(table);
    if (par.e) CatSetEndl(table);
    if (par.t) CatSetTab(table);
    if (par.v) CatSetNonPrintable(table);

    Cat(argc, argv, par, table);
  }

  return 0;
}
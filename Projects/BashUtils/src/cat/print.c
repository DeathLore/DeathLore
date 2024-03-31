#include "print.h"

void CatFile(FILE *file, param par, const char *table[static 256]) {
  int current = 0;
  int last = '\n';
  int sq_n = 0;
  int line = 0;

  while (fread(&current, 1, 1, file) > 0) {
    if (last == '\n') {
      if (par.s && current == '\n') {
        if (sq_n) continue;
        sq_n = 1;
      } else
        sq_n = 0;

      if (par.b) {
        if (current != '\n') printf("%6i\t", ++line);
      } else if (par.n) {
        printf("%6i\t", ++line);
      }
    }
    if (!*table[current])
      printf("%c", '\0');
    else
      printf("%s", table[current]);
    last = current;
  }
}

void Cat(int argc, char *argv[], param par, const char *table[static 256]) {
  for (char **filename = &argv[1], **end = &argv[argc]; filename != end;
       ++filename) {
    if (**filename == '-') continue;

    FILE *file = fopen(*filename, "rb");
    if (errno) {
      fprintf(stderr, "%s", argv[0]);
      perror(*filename);
      continue;
    }
    CatFile(file, par, table);
    fclose(file);
  }
}
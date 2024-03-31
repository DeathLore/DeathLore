#include "print.h"

#include "DL_grep.h"

int DL_grep(char *path, param par, char *template) {
  int error = 0;
  FILE *file = fopen(path, "r");
  if (file != NULL) {
    for (char sym = '0'; (sym = getc(file)) != EOF;) {
      char *line = calloc(256, 1);
      par.LinesNumber += 1;
      int length = 0;

      for (line[length] = '\0'; sym != EOF && sym != '\n'; sym = getc(file)) {
        line[length] = sym;
        line[length += 1] = '\0';
        if (length % 255 == 0) line = increaseStr(line, length + 256);
      }

      mainInfo(line, &par, template, path);
      free(line);
    }
    extraInfo(par, path);
    fclose(file);
  } else if (par.s == 0) {
    error = 1;
    // fclose(file); //Delete if problem
  }
  return error;
}

void extraInfo(param par, char *path) {
  if (par.c) {
    if (par.l) {
      par.FilesCounted > 1 ? printf("%s:\n", path) : printf("\n");
    } else {
      if (par.FilesCounted > 1) printf("%s:", path);
      printf("%i\n", par.MatchesCount);
    }
  }
  if (par.l && par.MatchesCount) printf("%s\n", path);
}

void mainInfo(char *line, param *par, char *template, char *path) {
  regex_t regex;
  if (regcomp(&regex, template,
              par->i ? REG_ICASE | REG_EXTENDED : REG_EXTENDED) == 0) {
    if (regexec(&regex, line, 0, NULL, 0) == par->v) {
      par->MatchesCount += 1;
      if ((par->c || par->l) == 0) {
        if (par->FilesCounted > 1 && !(par->h) && !(par->o))
          printf("%s:", path);
        if (par->n) printf("%i:", par->LinesNumber);
        if (!par->o)
          printf("%s\n", line);
        else
          paramO(regex, line, par, path);
      }
    }
    regfree(&regex);
  }
}

void paramO(regex_t regex, char *line, param *par, char const *const path) {
  while (regexec(&regex, line, 0, NULL, 0) == par->v) {
    char *buf = (char *)calloc(strlen(line) + 1, 1);
    strcpy(buf, line);
    int end = strlen(line);
    while (regexec(&regex, buf, 0, NULL, 0) == par->v) {
      end--;
      buf[strlen(buf) - 1] = 0;
    }
    buf[strlen(buf)] = line[strlen(buf)];
    int start = 0;
    while (regexec(&regex, buf, 0, NULL, 0) == par->v && strlen(buf) > 0) {
      start++;
      int j = 0;
      while (buf[j] != 0) {
        buf[j] = buf[j + 1];
        j++;
      }
    }
    start--;
    int i = strlen(buf);
    while (i != 0) {
      buf[i] = buf[i - 1];
      i--;
    }
    buf[0] = line[start];
    if (par->FilesCounted > 1 && !(par->h))
      printf("%s:%s\n", path, buf);
    else
      printf("%s\n", buf);
    free(buf);
    i = start + 1;
    while (line[i] != 0) {
      line[i - start - 1] = line[i];
      i++;
    }
    line[i - start - 1] = 0;
  }
}
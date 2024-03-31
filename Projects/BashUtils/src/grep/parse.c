#include "parse.h"

#include "DL_grep.h"

void parse_params(int argc, char **argv, param *par, char **template,
                  char *options, int retval[2]) {
  int res;

  while ((res = getopt(argc, argv, options)) != -1 && retval[0] == 0) {
    switch (res) {
      case 'i':
        par->i = 1;
        break;
      case 'v':
        par->v = 1;
        break;
      case 'c':
        par->c = 1;
        break;
      case 'l':
        par->l = 1;
        break;
      case 'n':
        par->n = 1;
        break;
      case 'h':
        par->h = 1;
        break;
      case 's':
        par->s = 1;
        break;
      case 'o':
        par->o = 1;
        break;
      case 'e':
        paramE(par, template, optarg);
        break;
      case 'f':
        retval[0] = paramF(par, template, optarg);
        break;

      case '?':
        retval[0] = 1;
        break;

      default:
        retval[0] = 1;
        break;
    }
  }
  if ((par->e || par->f) == 0) {
    initTemplate(template, argv[optind]);
    optind += 1;
  }

  if (par->o && (par->l || par->v || par->c)) par->o = 0;
  par->FilesCounted = argc - optind;

  retval[1] = optind;
}

void paramE(param *par, char **template, char *optarg) {
  if (!(par->e || par->f))
    par->e = initTemplate(template, optarg);
  else
    addTemplate(template, optarg);
}

int paramF(param *par, char **template, char *optarg) {
  int error = 0;
  FILE *file = fopen(optarg, "r");
  if (file != NULL) {
    for (char sym = '0'; (sym = getc(file)) != EOF;) {
      int length = 0;
      char *line = calloc(256, 1);

      for (line[length] = '\0'; sym != EOF && sym != '\n'; sym = getc(file)) {
        line[length] = sym;
        line[length += 1] = '\0';
        if (length % 255 == 0) line = (char *)increaseStr(line, length + 256);
      }

      if (!(par->e || par->f))
        par->f = initTemplate(template, line);
      else
        addTemplate(template, line);
      free(line);
    }
    fclose(file);
  } else if (par->s == 0) {
    error = 1;
  }
  return error;
}

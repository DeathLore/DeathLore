#ifndef PARSE_H
#define PARSE_H

#include "includes.h"

typedef struct {
  int e;  // Шаблон
  int i;  // Игнорирует различия регистра DONE
  int v;  // Инвертирует смысл поиска соответствий DONE
  int c;  // Выводит только количество совпадающих строк DONE
  int l;  // Выводит только совпадающие файлы DONE
  int n;  // Предваряет каждую строку вывода номером строки из файла ввода
  int h;  // Выводит совпадающие строки, не предваряя их именами файлов. DONE
  int s;  // Подавляет сообщения об ошибках о несуществующих или нечитаемых
          // файлах.
  int f;  // Получает регулярные выражения из файла.
  int o;  // Печатает только совпадающие (непустые) части совпавшей строки. DONE

  int FilesCounted;  //Количество файлов с совпадениями
  int LinesNumber;   //Количество строк с попаданиями
  int MatchesCount;  //Количество попаданий

} param;

void parse_params(int argc, char **argv, param *par, char **template,
                  char *options, int retval[2]);
int paramF(param *par, char **template, char *optarg);
void paramE(param *par, char **template, char *optarg);

#endif
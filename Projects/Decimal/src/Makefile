
FLAGS= -std=c11 -Wall -Wextra -Werror -g 

CC=gcc $(FLAGS)

CHECK_FLAGS = $(shell pkg-config --cflags --libs check)
#CHECK_FLAGS=-lcheck --coverage  -lm -lsubunit
CHECK_FLAGS += -lcheck --coverage 
ifeq ($(shell uname),Linux)
  CHECK_FLAGS += -lm -lsubunit
else
  CHECK_FLAGS += -fprofile-arcs -ftest-coverage
endif


REPOR_FLAGST=-fprofile-arcs -ftest-coverage


# все цели сразу
all: test gcov_report

# сборка библиотеки
DL_decimal.a: clean
	$(CC) -c functions/DL_*.c functions/helpers.c
	ar rcs DL_decimal.a *.o
	ranlib DL_decimal.a

# запуск тестов
test: DL_decimal.a
	$(CC) test/test_DL*.c test/DL_test.h DL_decimal.a -o testing $(CHECK_FLAGS)
	-./testing
	@sleep 1

# создание отчёта
gcov_report: DL_decimal.a
	$(CC) $(REPOR_FLAGST) functions/DL*.c -c
	$(CC) test/test_*.c -c
	$(CC) $(REPOR_FLAGST) *.o DL_decimal.a -o report_check $(CHECK_FLAGS)
	-./report_check
	lcov -t "gcovreport" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info
	@if [ `uname` = "Darwin" ]; then open -a 'google chrome' report/functions/index.html; fi

# очистка
clean:
	@rm -rf *.o *.a *.gcno *.gcda *.info
	@rm -rf report
	@rm -rf report_check
	@rm -rf testing
	@rm -rf testing.dSYM


# дополнительно
STYLE=-style=Google

format:
	-clang-format $(STYLE) -i ./*/*.c
	-clang-format $(STYLE) -i ./*/*.h
	-clang-format $(STYLE) -i ./*.h

check: test
	-clang-format $(STYLE) -n ./*/*.c
	-clang-format $(STYLE) -n ./*/*.h
	-clang-format $(STYLE) -n ./*.h

rebuild: all


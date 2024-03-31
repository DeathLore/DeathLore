FLAGS = -Wall -Wextra -Werror -Wuninitialized -std=c11 #-fsanitize=address
TESTFLAGS = -lcheck --coverage 
SOURCES_FUN:=$(wildcard DL_*.c)

ifeq ($(shell uname), Linux)
TESTFLAGS += -lm -lsubunit
else
TESTFLAGS += -fprofile-arcs -ftest-coverage
endif

all: DL_matrix.a
	rm -rf *.o

DL_matrix.a:
	gcc $(FLAGS) -c $(SOURCES_FUN)
	ar rcs DL_matrix.a *.o
	@ranlib DL_matrix.a

test: clean
	gcc $(FLAGS) -c $(SOURCES_FUN) test_matrix.c
	ar rcs DL_matrix.a *.o
	@ranlib DL_matrix.a
	@gcc *.c DL_matrix.a $(TESTFLAGS) -o testing.o 
	./testing.o

gcov_report: clean DL_matrix.a
	@gcc *.c DL_matrix.a $(TESTFLAGS) -o testing.o
	./testing.o
	@gcov -f *.gcda *.gcno
	@lcov --no-external -t "gcov_report" -o coverage.info -c -d . 
	@genhtml -o report coverage.info
	@open report/index.html

clang_fix:
	@clang-format --style=Google -i *.c *.h #test/*.c test/*.h

clang_check:
	@clang-format --style=Google -n *.c *.h #test/*.c test/*.h

clean:
	@rm -rf *.o testing.c testing *.a *.gcno *.gcda *.gcov *.info
	@rm -rf html_report DL_matrix.a DL_lib_test html_report
	@rm -rf report

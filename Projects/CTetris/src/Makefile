RM = rm -rf
CC := gcc
CFLAGS := -I inc -std=c11 -Wall -Wpedantic -Wextra
TESTFLAGS = -lcheck --coverage -fprofile-arcs -ftest-coverage
DEBUG = -g3 -DDEBUG

ifeq ($(shell uname), Linux)
TESTFLAGS += -lm -lsubunit
endif



SRC := ./gui/cli/cli_front.c ./brick_game/backend/*.c ./brick_game/tetris/*.c
TEST_SRC := ./brick_game/backend/brick_backend.c ./brick_game/backend/OG_timer.c ./brick_game/tetris/finite_machine_logic.c ./brick_game/tetris/tetris_backend.c
OUT := ./compiled/*.o

all: install

install: compile
	$(CC) $(CFLAGS) $(OUT) -lncurses -o tetris
	mv tetris games/tetris

test: test_compile
	$(CC) ./tests/test.c lTetris.a $(TESTFLAGS) -o testing
	@echo "\n\n"
	./testing
	@$(RM) games_data

compile:
	@mkdir -p compiled
	$(CC) $(CFLAGS) -DTETRIS -D_cli -c $(SRC)
	mv *.o compiled/

test_compile: clean del_saves
	@mkdir -p compiled
	$(CC) $(CFLAGS) -DTETRIS -D_cli -DTESTING $(TESTFLAGS) -c $(TEST_SRC)
	ar rcs lTetris.a *.o
	@ranlib lTetris.a
	@mv *.o compiled/

gcov_report: test
	@mkdir -p report
	@gcov -f *.gcda *.gcno
	@lcov --no-external -t "gcov_report" -o coverage.info -c -d . 
	@genhtml -o report coverage.info
	@open report/index.html

	@mv *.gcno report/
	@mv *.gcda report/
	@mv *.gcov report/
	@mv *.info report/

unistall: clean del_saves
	$(RM) games/tetris

del_saves:
	@$(RM) games_data

dvi_open:
	open docs/html/index.html

dvi: dvi_clean
	doxygen docs/Doxyfile
	mv html docs
	mv latex docs

dvi_clean:
	$(RM) docs/html docs/latex

dist: install
	tar -czvf Tetris.tar.gz games/tetris

clang_fix:
	@clang-format -style=Google -i brick_game/backend/*.? brick_game/tetris/*.? gui/cli/*.? tests/test.c

clang_check:
	@clang-format -style=Google -n brick_game/backend/*.? brick_game/tetris/*.? gui/cli/*.? tests/test.c

clean: dvi_clean
	$(RM) compiled/ *.o Tetris.tar.gz lTetris.a testing *.gcda *.gcno *.gcov *.info report

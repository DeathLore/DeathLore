CC=g++
FLAGS=-Wall -Wextra -Werror -std=c++17
TEST_FLAGS=-lgtest -lgtest_main -lpthread
TEST = test/test
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

TEST_SRC = $(wildcard $(TEST)*.cpp)
TEST_OBJ = $(patsubst $(TEST)%.cpp, $(TEST)%.o, $(TEST_SRC))

ifeq ($(shell uname -s),Linux)
	TEST_FLAGS += -lsubunit -lgcov -lrt
endif

all: DL_matrix_oop.a

DL_matrix_oop.a: $(OBJ)
	ar rc DL_matrix_oop.a $^
	ranlib DL_matrix_oop.a

test.a: $(TEST_OBJ)
	ar rc $(TEST).a $^
	ranlib $(TEST).a

covered:
	$(CC) $(FLAGS) -c $(SRC) -fprofile-arcs -ftest-coverage
	ar rc DL_matrix_oop.a $(OBJ)
	ranlib DL_matrix_oop.a

style: clean
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.cpp *.h
	rm .clang-format
	
test: clean covered test.a
	$(CC) $(FLAGS)  -o $(TEST).o $(TEST).cpp -c
	$(CC) $(TEST).o $(TEST).a DL_matrix_oop.a -o $(TEST) -fprofile-arcs -ftest-coverage $(FLAGS) $(TEST_FLAGS)
	./$(TEST)

leaks: test
ifeq ($(shell uname -s), Linux)
	valgrind --leak-check=yes  ./$(TEST)
else
	leaks --atExit -- ./$(TEST)
endif

gcov_report: test
	gcov -f *.gcda *.gcno
	lcov --no-external -t "gcov_report" -o coverage.info -c -d . 
	genhtml -o report coverage.info
	open report/index.html

clean:
	rm -rf *.o *.a *.gcda *.gcno *.gcov *.info *.html $(TEST)*.gcda $(TEST)*.gcno $(TEST)*.o $(TEST)*.a $(TEST) gcov_report

clean_gcov: clean
	rm -rf ./report

rebuild: clean all




CFLAGS = -Wall -Werror -Wextra -std=c11 -IIncludes
CFLAGSNOERR = -fsanitize=address -std=c11 -IIncludes

all: DL_grep

DL_grep: parse print grep 
	gcc $(CFLAGS) ex_files/parse.o ex_files/print.o ex_files/grep.o -o DL_grep

parse: 
	gcc $(CFLAGS) -c parse.c -o ex_files/parse.o

print: 
	gcc $(CFLAGS) -c print.c -o ex_files/print.o 

grep: 
	gcc $(CFLAGS) -c DL_grep.c -o ex_files/grep.o


rebuild: clean 
	rm DL_grep 
	make all

clean: 
	rm -rf ex_files/*.o
	rm DL_grep

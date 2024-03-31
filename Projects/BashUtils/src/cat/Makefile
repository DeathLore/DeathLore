CFLAGS = -Wall -Werror -Wextra -std=c11 -IIncludes


all: DL_cat

DL_cat: parse print cat tables
	gcc $(CFLAGS) ex_files/tables.o ex_files/parse.o ex_files/print.o ex_files/cat.o -o DL_cat

parse:
	gcc $(CFLAGS) -c parse.c -o ex_files/parse.o
print:
	gcc $(CFLAGS) -c print.c -o ex_files/print.o
cat:
	gcc $(CFLAGS) -c DL_cat.c -o ex_files/cat.o
tables:
	gcc $(CFLAGS) -c tables.c -o ex_files/tables.o

rebuild: clean
	rm DL_cat
	make all
clean:
	rm -rf ex_files/*.o

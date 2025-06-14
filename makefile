

CC = g++
CFLAGS = -Wall -Wextra -O3 -g
SRC = lazy_wordle.cpp



lazy_wordle: objs/lazy_wordle.o objs/wordle.o objs/utils.o objs/wordle_solver.o objs/words.o objs/results.o
	$(CC) $(CFLAGS) objs/lazy_wordle.o objs/wordle.o objs/utils.o \
	 objs/wordle_solver.o objs/words.o objs/results.o -o lazy_wordle

objs/lazy_wordle.o: lazy_wordle.cpp wordle.hpp utils.hpp wordle_solver.hpp
	mkdir -p objs
	$(CC) $(CFLAGS) -c lazy_wordle.cpp -o objs/lazy_wordle.o

objs/wordle.o: wordle.cpp wordle.hpp utils.hpp
	mkdir -p objs
	$(CC) $(CFLAGS) -c wordle.cpp -o objs/wordle.o

objs/utils.o: utils.cpp utils.hpp
	mkdir -p objs

	$(CC) $(CFLAGS) -c utils.cpp -o objs/utils.o

objs/wordle_solver.o: wordle_solver.cpp wordle_solver.hpp wordle.hpp utils.hpp
	mkdir -p objs
	$(CC) $(CFLAGS) -c wordle_solver.cpp -o objs/wordle_solver.o

objs/words.o: words.txt
	mkdir -p objs
	objcopy --input binary --output elf64-x86-64 --binary-architecture i386 words.txt objs/words.o 

objs/results.o: results.txt
	mkdir -p objs
	objcopy --input binary --output elf64-x86-64 --binary-architecture i386 results.txt objs/results.o 

clean:
	rm -f objs/*.o lazy_wordle




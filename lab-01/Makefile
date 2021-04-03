main: obj/main.o obj/algorithm.o obj/util.o obj/io.o | obj
	gcc obj/main.o obj/algorithm.o obj/util.o obj/io.o -o main

obj:
	mkdir obj

obj/main.o: src/main.c include/algorithm.h include/io.h include/util.h | obj
	gcc -c -I include src/main.c -o obj/main.o

obj/algorithm.o: include/algorithm.h include/io.h include/util.h | obj
	gcc -c -I include src/algorithm.c -o obj/algorithm.o

obj/io.o: src/io.c include/io.h | obj
	gcc -c -I include src/io.c -o obj/io.o

obj/util.o: src/util.c include/util.h include/io.h | obj
	gcc -c -I include src/util.c -o obj/util.o

.PHONY: clean
clean:
	rm -rf main obj

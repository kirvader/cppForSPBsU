test: obj/test.o obj/str.o obj/test_str.o | obj
	gcc obj/test.o obj/str.o obj/test_str.o -o test

obj:
	mkdir obj

obj/test.o: src/test.c include/str.h | obj
	gcc -c -I include src/test.c -o obj/test.o

obj/str.o: src/str.c include/str.h | obj
	gcc -c -I include src/str.c -o obj/str.o

obj/test_str.o: src/test_str.c include/test_str.h include/str.h | obj
	gcc -c -I include src/test_str.c -o obj/test_str.o

.PHONY: clean
clean:
	rm -rf test obj

hw_01: obj/main.o obj/bmp.o | obj
	gcc obj/main.o obj/bmp.o -o hw_01

obj:
	mkdir obj

obj/main.o: src/main.c include/bmp.h | obj
	gcc -c -I include src/main.c -o obj/main.o

obj/bmp.o: src/bmp.c include/bmp.h | obj
	gcc -c -I include src/bmp.c -o obj/bmp.o

.PHONY: clean
clean:
	rm -rf hw_01 obj


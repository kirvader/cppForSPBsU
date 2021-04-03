lab_05: obj/main.o obj/clist.o obj/point_list.o | obj
	gcc obj/main.o obj/clist.o obj/point_list.o -o lab_05

obj:
	mkdir obj

obj/main.o: src/main.c include/clist.h | obj
	gcc -c -I include src/main.c -o obj/main.o

obj/clist.o: src/clist.c include/clist.h | obj
	gcc -c -I include src/clist.c -o obj/clist.o

obj/point_list.o: src/point_list.c include/point_list.h | obj
	gcc -c -I include src/point_list.c -o obj/point_list.o

.PHONY: clean
clean:
	rm -rf lab_05 obj


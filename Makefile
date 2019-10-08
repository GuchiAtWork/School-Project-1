all: dict1 dict2	

dict1: dict1.o info.o input.o tree.o
	gcc -Wall -o dict1 dict1.o info.o input.o tree.o

dict2: dict2.o info.o input.o tree.o
	gcc -Wall -o dict2 dict2.o info.o input.o tree.o

tree.o: tree.c tree.h input.h info.h
	gcc -Wall -c tree.c

input.o: input.c input.h tree.h info.h
	gcc -Wall -c input.c

info.o: info.c info.h tree.h input.h
	gcc -Wall -c info.c

dict1.o: dict1.c input.h tree.h info.h
	gcc -Wall -c dict1.c

dict2.o: dict2.c input.h tree.h info.h
	gcc -Wall -c dict2.c

clean:
	@rm -f *.o

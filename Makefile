CFLAGS= -Wall -Werror

morpion: ia.c morpion.c ia.h morpion.h
	gcc $(CFLAGS) ia.c morpion.c -o morpion

clean:
	-rm -f *.o *~

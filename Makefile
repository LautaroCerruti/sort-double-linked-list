all: generador programa

generador:
	gcc -Wall -Werror -o generador ./GeneradorPersonas/main.c

programa: glist.o persona.o
	gcc -Wall -Werror -o main main.c glist.o persona.o

glist.o: ./GList/glist.c
	gcc -Wall -Werror -c ./GList/glist.c

persona.o: ./Persona/persona.c
	gcc -Wall -Werror -c ./Persona/persona.c

clean:
	rm -f programa *.o
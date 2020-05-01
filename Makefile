all: generador programa

generador:
	gcc -o generador ./GeneradorPersonas/main.c

programa: glist.o persona.o
	gcc -o main main.c glist.o persona.o

glist.o: ./GList/glist.c
	gcc -c ./GList/glist.c

persona.o: ./Persona/persona.c
	gcc -c ./Persona/persona.c

clean:
	rm -f programa *.o
all: generador programa

generador:
	gcc -Wall -Wextra -Werror -g -std=99 -o generador ./GeneradorPersonas/main.c

programa: glist.o persona.o
	gcc -Wall -Wextra -Werror -g -std=99 -o main main.c glist.o persona.o

glist.o: ./GList/glist.c
	gcc -Wall -Wextra -Werror -g -std=99 -c ./GList/glist.c

persona.o: ./Persona/persona.c
	gcc -Wall -Wextra -Werror -g -std=99 -c ./Persona/persona.c

clean:
	rm -f programa *.o
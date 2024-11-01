compile: clean logica.o entradaSaida.o
	gcc logica.o entradaSaida.o main.c -o main

logica.o: prototipos.h logica.c
	gcc -c logica.c

entradaSaida.o: prototipos.h entradaSaida.c
	gcc -c entradaSaida.c

clean:
	rm -rf *.o main
run: clean main
	./main

main: logica.o entradaSaida.o
	gcc logica.o entradaSaida.o main.c -o main

logica.o: logica.h logica.c
	gcc -c logica.c

entradaSaida.o: entradaSaida.h entradaSaida.c
	gcc -c entradaSaida.c

clean:
	rm -rf *.o main
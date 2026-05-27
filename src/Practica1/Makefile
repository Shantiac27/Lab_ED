cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g
includes = -I ../src/iostring -I ../src/structures/lista
libs = ../../lib -liostring -lLista
source = $(wildcard *.c) 
output = ../../bin/Practica1

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
rebuild:
	make -C ..\iostring
	make -C ..\structures\nodos
	make -C ..\structures\lista
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
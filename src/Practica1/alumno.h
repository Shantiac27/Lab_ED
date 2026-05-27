//Alumno.h

#ifndef ALUMNO_H
#define ALUMNO_H

#include <stdio.h>
#include "../iostring/iostring.h"
#include "../structures/lista/lista.h"
#define LEN 64


typedef struct
{
	unsigned int matricula;
	char nombre[LEN];
	int semestres;
	float promedio;
	
}Alumno;

Alumno *crearAlumno(Lista lista);
void imprimirAlumno(void *dato);
int compararMatricula(void *datoA, void *datoB);
int compararNombre(void *datoA, void *datoB);
int compararSemestre(void *datoA, void *datoB);
int compararPromedio(void *datoA, void *datoB);
int compararAlumno(void *datoA, void *datoB);


#endif


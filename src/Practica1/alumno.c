//Alumno.c

#include "alumno.h"



Alumno* crearAlumno(Lista lista)
{
	Alumno *nuevo = calloc(1,sizeof(Alumno));
	inputEnteroSinSigno("\n Matricula: ",&nuevo->matricula);
	Resultado res = buscar(lista,&nuevo->matricula);
	if(res.enco)
	{
		printf("Matricula ya registrada");
		imprimirResultado(lista,res);
		return NULL;
	}
	inputCadena("\n Nombre: ",nuevo->nombre,LEN);
	inputEntero("\n Semestres: ",&nuevo->semestres);
	inputFloat("\n Promedio: ",&nuevo->promedio);
	return nuevo;	
}

void imprimirAlumno(void *dato)
{
	Alumno *alumno = dato;
	printf("%u | ",alumno->matricula);
	printf("%-40s |",alumno->nombre);
	printf("%-2d |",alumno->semestres);
	printf("%.2f ", alumno->promedio);
	printf("\n");
}

int compararMatricula(void *datoA, void *datoB)
{
	Alumno *alumA = datoA, *alumB = datoB;
	return alumA->matricula - alumB->matricula;
}

int compararNombre(void *datoA, void *datoB)
{
	Alumno *alumA = datoA, *alumB = datoB;
	return strcmp(alumA->nombre,alumB->nombre);
}

int compararSemestre(void *datoA, void *datoB)
{
	Alumno *alumA = datoA, *alumB = datoB;
	return alumA->semestres - alumB->semestres;
}

int compararPromedio(void *datoA, void *datoB)
{
	Alumno *alumA = datoA, *alumB = datoB;
	if(alumA->promedio < alumB->promedio) return -1;
	else if(alumA->promedio > alumB->promedio) return 1;
	else return 0;
}

int compararAlumno(void *datoA, void *datoB)
{
	return 0;
}
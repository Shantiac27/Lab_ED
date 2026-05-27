//Pila.h

#ifndef PILA_H
#define PILA_H
#include <stdio.h>
#include <stdlib.h>
#include "../nodos/nodo.h"

typedef struct
{
	Nodo *cima;
	int cantidad;
	int capacidad;
	void (*imprimir)(void*);
	void (*liberar)(void*);
}Pila;

//Verificación
int pilaVacia(Pila pila);
int pilaLlena(Pila pila);

//Datos
void pushDato(Pila *pila, void  *dato);
void* popDato(Pila *pila);
void pushNodo(Pila  *pila, Nodo *nodo);
Nodo* popNodo(Pila *pila);

//Vaciar/eliminar pila
void vaciarPila(Pila *pila);
void eliminarPila(Pila *pila);

//Imprimir pila
void imprimirPila(Pila pila);

//ordenar
void ordenarPila(Pila *pila,int (*comparar)(void*,void*));

#endif

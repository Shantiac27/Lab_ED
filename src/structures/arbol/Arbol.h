//Arbol.h

#ifndef ARBOL_H
#define ARBOL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../nodos/nodoarbol.h"
#include "../pila/Pila.h"

#define PREORDEN 1
#define ORDEN 2
#define INVERSO 3
#define POSTORDEN 4

#define IZQUIERDA 0
#define DERECHA 1

typedef struct
{
	NodoA *padre;
	NodoA *nodo;
	void *dato;
	int rama;
}Resultado;

typedef struct
{
	NodoA *raiz;
	int cantidad;
	void (*imprimir) (void*);
	int (*comparar) (void*,void*);
	void (*liberar) (void*);
}Arbol;

void imprimirEntero(void *dato);
void imprimirCadena(void *dato);

int compEntero( void *a,void *b);
int compCadenas( void *a,void *b);

void buscarEnArbol(NodoA *raiz, void *dato, int *resultado,int (*comparar)(void*,void*));
void invertir(Arbol *arbol);

void guardarArbolEnPila(Arbol *arbol, Pila *pila);
void guardarNodoEnPila(NodoA *raiz, Pila *pila);

int compararArbolesRec(NodoA *n1, NodoA *n2, int (*comparar)(void*, void*));
int compararNodos(NodoA *raiz1, NodoA *raiz2,int(*comparar)(void*, void*));
int compararArboles(Arbol arbol1, Arbol arbol2);

void imprimirResultado(Resultado resultado);
NodoA* eliminarNodo(NodoA *raiz, void *dato, int (*comparar)(void*, void*), void (*liberar)(void*));
Arbol eliminarDatoEnArbol(Arbol arbol, void *dato, int (*comparar)(void*,void*));

void calcularProfundidad(NodoA *raiz, int nivel, int *profundidad);
void profundidad(Arbol arbol);
Arbol balancearArbol(Arbol arbol);

void guardarEnArreglo(NodoA *raiz, void **arr, int *index);
NodoA* construirBalanceado(void **arr, int inicio, int fin);

void eliminarArbol(Arbol *arbol);
void insertarArbol(Arbol *arbol, void *dato);
void imprimirArbol(Arbol arbol);
void imprimirOrden(Arbol arbol, int opcion);

void insertarArbolOrdenado(NodoA *raiz,void *dato,int (*comparar)(void*,void*));
void imprimir_arbol(NodoA* nodo, int nivel,void (*imprimir)(void*));

void preorden(NodoA *raiz,void (*imprimir)(void*));
void orden(NodoA *raiz,void (*imprimir)(void*));
void inverso(NodoA *raiz,void (*imprimir)(void*));
void postorden(NodoA *raiz,void (*imprimir)(void*));

void eliminar_NodosA(NodoA *raiz,void (*liberar)(void*));

#endif
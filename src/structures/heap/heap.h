//heap.h
#ifndef HEAD_H
#define HEAD_H

#include "../nodos/nodoarbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pila.h>

#define HEAP_MIN 0
#define HEAP_MAX 1

typedef int (*fn_comparar)(void*, void*);
typedef void (*fn_imprimir)(void*);

typedef struct
{
	char* nombre;
	int paginas;
}Archivo;

typedef struct
{
	unsigned char tipo;
	int cantidad;
	void **datos;
	NodoA *raiz;
	fn_comparar comparar;
	fn_imprimir imprimir;
}Heap;

Heap crearHeap(unsigned char tipo, fn_comparar comparar, fn_imprimir imprimir);
void insertarHeap(Heap *heap, void *dato);
void* eliminarHeap(Heap *heap);
void imprimirHeap(Heap heap);

void heapify_min(Heap *heap, int padre);
void heapify(Heap *heap);
void cambiarPrioridad(Heap *heap);
void* eliminarDatoHeap(Heap *heap, int indice);
void destruirHeap(Heap *heap);

void crearHeapArbol(Heap *heap);
void insertarArbolHeap(NodoA *raiz, void **datos, int padre, int cantidad);
void imprimir_heap_arbol(NodoA *nodo, int nivel, void (*imprimir)(void*));
void imprimirHeapArbol(Heap heap);
void eliminar_NodosA(NodoA *raiz);
void eliminarHeapArbol(Heap *heap);

void imprimirArchivo(void *doc);
Archivo* crearArchivo(char* nom, int pag);
int compararArchivo(void*a,void*b);

#endif
#ifndef NODOA_H
#define NODOA_H
#include <stdio.h>
#include <stdlib.h>

typedef struct nodoA
{
	void *dato;
	struct nodoA *izq;
	struct nodoA *dch;
}NodoA;

NodoA* crearNodoA(void *dato);

#endif
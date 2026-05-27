//NodoD.h

#ifndef NODOD_H
#define NODOD_H
#include <stdlib.h>


typedef struct nodo
{
	void *dato;
	struct nodo *sig;
	struct nodo *ant;
}NodoD;

NodoD* crearNodoD(void *dato);


#endif
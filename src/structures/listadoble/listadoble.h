//Lista enlazada doble

#ifndef LISTAD_H
#define LISTAD_H

#include <stdio.h>
#include "../nodos/nododoble.h"

typedef struct
{
	NodoD *inicio;
	NodoD *fin;
	int cant;
	void (*imprimir)(void*); //APUNTADOR A FUNCION
	int (*comparar)(void*,void*);
	void (*liberar)(void*);
}ListaD;

typedef struct
{
	NodoD *ante;
	NodoD *enco;
	void *dato;	
}Resultado;

//Struck resultado
Resultado buscar(ListaD lista,void *dato);
void imprimirResultado(ListaD lista,Resultado resultado);

//IMPLEMENTACIONES
void imprimirListaDIF(ListaD lista);
void imprimirListaDFI(ListaD lista);
void insertarFinalD(ListaD *lista, void *dato);

void borrarInicioD(ListaD *lista);
void borrarListaD(ListaD *lista);

ListaD inicializarListaD(void);

void insertarEnOrden(ListaD *lista, void *dato);
void insertarInicioD(ListaD*, void*);
int insertarEn(ListaD *lista, void *dato, int index);

int borrarEnD(ListaD *lista, int index);
void borrarFinD(ListaD *lista);
void borrarDatoD(ListaD *lista, void *dato);
void reordenar (ListaD *lista, int (*comparar) (void*, void*));

#endif  
//Pila.c

#include "Pila.h"

//Verificacion
int pilaVacia(Pila pila)
{
	return pila.cima == NULL && pila.cantidad==0;
}

int pilaLlena(Pila  pila)
{
	return pila.cantidad == pila.capacidad;
}

//Datos

void pushDato(Pila *pila, void  *dato)
{
	if(pilaLlena(*pila))
	{
		printf("OVERFLOW");
		return;
	}
	Nodo *nuevaCima = crearNodo(dato);
	nuevaCima->sig = pila->cima;
	pila->cima = nuevaCima;
	pila->cantidad++;
}

void* popDato(Pila *pila)
{
	void *dato = NULL;
	if(pilaVacia(*pila))
	{
		printf("UNDERFLOW");
		return dato;
	}
	Nodo *cimaVieja = pila->cima;
	pila->cima = pila->cima->sig;
	dato = cimaVieja->dato;
	free(cimaVieja);
	pila->cantidad--;
	return dato;
	
}

void pushNodo(Pila  *pila, Nodo *nodo)
{
	if(pilaLlena(*pila))
	{
		printf("OVERFLOW");
		return;
	}
	nodo->sig = pila->cima;
	pila->cima = nodo;
	pila->cantidad++;
}

Nodo* popNodo(Pila *pila)
{
	Nodo *cimaVieja = NULL;
	if(pilaVacia(*pila))
	{
		printf("UNDERFLOW");
		return cimaVieja;
	}
	cimaVieja = pila->cima;
	pila->cima = pila->cima->sig;
	pila->cantidad--;
	cimaVieja->sig = NULL;
	return cimaVieja;
}

//Vaciar/Eliminar pila
void vaciarPila(Pila *pila)
{
	while(!pilaVacia(*pila))
	{
		popDato(pila);
	}
}

void eliminarPila(Pila *pila)
{
	while(!pilaVacia(*pila))
	{
		void *dato = popDato(pila);
		if(pila->liberar)
			pila->liberar(dato);
	}
}

//Imprimir respetar LIFO
void imprimirPila(Pila pila)
{
	Pila aux = {NULL,0,-1,NULL,NULL};
	printf("\n[%d]PILA:",pila.cantidad);
	//IMPRIMIR CIMAS ORIGINAL
	//REMOVER LOS NODOS DE LA ORIGINAL
	//PASARLOS A LA AUX
	while(!pilaVacia(pila))
	{
		printf("\n");
		pila.imprimir(pila.cima->dato);
		pushNodo(&aux, popNodo(&pila));
	}
	//RESTAURAR
	//REMOVER LOS NODOS DE LA AUX
	//PASARLOS A LA ORIGINAL
	while(!pilaVacia(aux))
	{
		pushNodo(&pila,popNodo(&aux));
	}
}

void ordenarPila(Pila *pila, int (*comparar)(void*,void*))
{
	Pila aux = {NULL,0,-1,NULL,NULL};

    while(!pilaVacia(*pila))
    {
        Nodo* temp = popNodo(pila);

        // Mover de aux a pila mientras sean menores
        while(!pilaVacia(aux) &&
              comparar(aux.cima->dato, temp->dato) < 0) //aux.cima < temp.dato
        {
            pushNodo(pila, popNodo(&aux));
        }

        pushNodo(&aux, temp);
    }

    // Regresar todo a la pila original
    while(!pilaVacia(aux))
    {
        pushNodo(pila, popNodo(&aux));
    }
}

#include "heap.h"


Heap crearHeap(unsigned char tipo, fn_comparar comparar, fn_imprimir imprimir)
{
	Heap heap = {tipo,0,NULL,NULL,comparar,imprimir};
	return heap;
}

void insertarHeap(Heap *heap, void *dato)
{
	void **aux = NULL;
	if(!heap->cantidad)
		heap->datos = calloc(1,sizeof(void*));
	else
	{
		while(!aux)
			aux = realloc(heap->datos,(heap->cantidad+1) * sizeof(void*));
		heap->datos = aux;
	}
	
	heap->datos[heap->cantidad++] = dato;
	
	heapify(heap);
}

void* eliminarHeap(Heap *heap)
{
	void *dato = NULL;
	if(!heap->cantidad)
		return dato;
	dato = heap->datos[0];
	if(heap->cantidad == 1)
	{
		free(heap->datos);
		heap->datos = NULL;
		heap->cantidad--;
		return dato;
	}
	heap->datos[0] = heap->datos[heap->cantidad-1];
	void **aux = NULL;
	while(!aux)
		aux = realloc(heap->datos,(heap->cantidad-1) * sizeof(void*));
	heap->datos = aux;
	heap->cantidad--;
	heapify(heap);
	return dato;
}

void imprimirHeap(Heap heap)
{
	printf("\n HEAP: \n");
	if(heap.cantidad)
	{
		for( int i = 0; i<heap.cantidad; i++)
		{
			printf(" [%d] ",i);
			heap.imprimir(heap.datos[i]);
			printf("\n");
		}
	}
	else
	{
		printf("VACIO");
	}
}


void heapify_min(Heap *heap, int padre)
{
	if(padre<0 || padre > (heap->cantidad/2-1))
		return;
	int min = padre;
	int izq = 2*padre+1;
	int dch = 2*padre+2;
	switch(heap->tipo)
	{
		case HEAP_MIN:
			if(izq < heap->cantidad && heap->comparar(heap->datos[min],heap->datos[izq])>0)
				min = izq;
			if(dch < heap->cantidad && heap->comparar(heap->datos[min],heap->datos[dch])>0)
				min = dch;
			break;
		case HEAP_MAX:
			if(izq < heap->cantidad && heap->comparar(heap->datos[izq],heap->datos[min])>0)
				min = izq;
			if(dch < heap->cantidad && heap->comparar(heap->datos[dch],heap->datos[min])>0)
				min = dch;
			break;
	}
	
	if(min!=padre)
	{
		void *dato = heap->datos[padre];
		heap->datos[padre] = heap->datos[min];
		heap->datos[min] = dato;
		heapify_min(heap,min);
	}
}

void heapify(Heap *heap)
{
	for(int i = heap->cantidad/2 - 1; i >= 0; i--)
        heapify_min(heap, i);
	if(heap->raiz)
		eliminarHeapArbol(heap);
	crearHeapArbol(heap);
}

void crearHeapArbol(Heap *heap)
{
	if(!heap->cantidad)
		return;
	heap->raiz = crearNodoA(heap->datos[0]);
	insertarArbolHeap(heap->raiz, heap->datos, 0,heap->cantidad);
}

void insertarArbolHeap(NodoA *raiz, void **datos, int padre, int cantidad)
{	
	int izquierda = 2*padre+1;
	int derecha = 2*padre+2;
	
	if(izquierda >= cantidad)
		return;
	raiz->izq = crearNodoA(datos[izquierda]);
	insertarArbolHeap(raiz->izq, datos, izquierda, cantidad);
	if(derecha >= cantidad)
		return;
	raiz->dch = crearNodoA(datos[derecha]);
	insertarArbolHeap(raiz->dch, datos, derecha, cantidad);
}

void imprimir_heap_arbol(NodoA *nodo, int nivel, void (*imprimir)(void*))
{
	int i;
	if(nodo != NULL)
	{
		printf(" ");
		imprimir(nodo->dato);
		if(nodo->dch)
		{
			printf("\n");
			for(i = 0; i < nivel+1; i++)
			{
				if(i == nivel)
					printf(" |___R ");
				else
					printf(" |     ");
			}
			imprimir_heap_arbol(nodo->dch,nivel+1,imprimir);
		}
		if(nodo->izq)
		{
			printf("\n");
			for(i = 0; i < nivel + 1; i++)
			{
				printf(" |     ");
			}
			printf("\n");
			for(i = 0; i<nivel+1;i++)
			{
				if(i == nivel)
					printf(" |___L ");
				else
			        printf(" |     ");
			}
			imprimir_heap_arbol(nodo->izq, nivel+1, imprimir);
		}
	}
}

void imprimirHeapArbol(Heap heap)
{
	if(heap.raiz)
		imprimir_heap_arbol(heap.raiz,0,heap.imprimir);
	else
		printf("\nVACIO");
}

void eliminar_NodosA(NodoA *raiz)
{
	if(!raiz)
		return;
	eliminar_NodosA(raiz->izq);
	eliminar_NodosA(raiz->dch);
	//LIBERAR
	free(raiz);
}


void eliminarHeapArbol(Heap *heap)
{
	eliminar_NodosA( heap->raiz);
	heap->raiz = NULL;
}

void cambiarPrioridad(Heap *heap)
{
	if(heap->tipo == HEAP_MAX)
		heap->tipo = HEAP_MIN;
	else
		heap->tipo = HEAP_MAX;
	
	printf("\nPRIORIDAD CAMBIADA");
	heapify(heap);
}

void imprimirArchivo(void *doc)
{
	Archivo *archivo = doc;
	printf("%s - %d", archivo->nombre, archivo->paginas);
}

Archivo* crearArchivo(char* nom, int pag)
{
	Archivo *archivo = malloc(sizeof(Archivo));
	archivo->nombre = strdup(nom);
	archivo->paginas = pag;
	return archivo;
}

int compararArchivo(void*a,void*b)
{
	Archivo *aa = a,*bb=b;
	if(aa->paginas==bb->paginas)return 0;
	else if(aa->paginas < bb->paginas)return -1;
	else return 1;
}

void* eliminarDatoHeap(Heap *heap, int indice)
{
	if(indice == 0)
	{
		return eliminarHeap(heap);
	}
	
	void *dato = NULL;
	if(!heap->cantidad || indice>=heap->cantidad)
		return dato;
	
	dato = heap->datos[indice];
	
	if(indice == heap->cantidad-1)
	{
		free(heap->datos[indice]);
		heap->datos[indice] = NULL;
		heap->cantidad--;
		return dato;
	}
	
	heap->datos[indice] = heap->datos[heap->cantidad-1];
	
	void **aux = NULL;
	while(!aux)
		aux = realloc(heap->datos,(heap->cantidad-1) * sizeof(void*));
	heap->datos = aux;
	heap->cantidad--;
	heapify(heap);
	return dato;
}

void destruirHeap(Heap *heap)
{
	while(heap->cantidad)
	{
		void *dato = eliminarHeap(heap);
		free(dato);
	}
	if(heap->raiz)
		eliminarHeapArbol(heap);
}
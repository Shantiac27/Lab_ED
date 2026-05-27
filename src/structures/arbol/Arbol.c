//Arbol.c

#include "Arbol.h"


void insertarArbolOrdenado(NodoA *raiz, void *dato, int (*comparar)(void*,void*))
{
	if(comparar(dato,raiz->dato)<=0)
	{
		//IZQUIERDA	
		if(!raiz->izq)
			raiz->izq = crearNodoA(dato);
		else if(!raiz->dch && comparar(dato,raiz->dato) == 0)
			raiz->dch = crearNodoA(dato);
		else
			insertarArbolOrdenado(raiz->izq,dato,comparar);
	}
	else
	{
		//DERECHA
		if(raiz->dch)
			insertarArbolOrdenado(raiz->dch,dato,comparar);
		else
			raiz->dch = crearNodoA(dato);
	}
}

void insertarArbol(Arbol *arbol, void *dato)
{
	if(!arbol->raiz)
		arbol->raiz = crearNodoA(dato);
	else
		insertarArbolOrdenado(arbol->raiz,dato,arbol->comparar);
	arbol->cantidad++;
}

void imprimir_arbol(NodoA *nodo, int nivel, void (*imprimir)(void*))
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
			imprimir_arbol(nodo->dch,nivel+1,imprimir);
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
			imprimir_arbol(nodo->izq, nivel+1, imprimir);
		}
	}
}

void imprimirArbol(Arbol arbol)
{
	imprimir_arbol(arbol.raiz,0,arbol.imprimir);
}

void preorden(NodoA *raiz, void (*imprimir)(void*))
{
	if(!raiz)
		return;
	printf(" ");
	imprimir(raiz->dato);
	preorden(raiz->izq, imprimir);
	preorden(raiz->dch, imprimir);
}

void orden(NodoA *raiz, void (*imprimir)(void*))
{
	if(!raiz)
		return;
	orden(raiz->izq,imprimir);
	printf(" ");
	imprimir(raiz->dato);
	orden(raiz->dch,imprimir);
}

void inverso(NodoA *raiz, void (*imprimir)(void*))
{
	if(!raiz)
		return;
	inverso(raiz->dch,imprimir);
	printf(" ");
	imprimir(raiz->dato);
	inverso(raiz->izq,imprimir);
}

void postorden(NodoA *raiz, void (*imprimir)(void*))
{
	if(!raiz)
		return;
	postorden(raiz->izq,imprimir);
	postorden(raiz->dch,imprimir);
	printf(" ");
	imprimir(raiz->dato);
}

void imprimirOrden(Arbol arbol, int opcion)
{
	switch(opcion)
	{
		case PREORDEN:
		    preorden(arbol.raiz,arbol.imprimir);
		    break;
		case ORDEN:
		    orden(arbol.raiz,arbol.imprimir);
			break;
		case INVERSO:
		    inverso(arbol.raiz,arbol.imprimir);
			break;
		case POSTORDEN:
		    postorden(arbol.raiz,arbol.imprimir);
			break;
	}
}

void eliminar_NodosA(NodoA *raiz,void (*liberar)(void*))
{
	if(!raiz)
		return;
	eliminar_NodosA(raiz->izq,liberar);
	eliminar_NodosA(raiz->dch,liberar);
	//LIBERAR
	if(liberar)
		liberar(raiz->dato);
	free(raiz);
}


void eliminarArbol(Arbol *arbol)
{
	eliminar_NodosA( arbol->raiz, arbol->liberar);
	arbol->raiz = NULL;
	arbol->cantidad = 0;
}

void invertirRamas(NodoA *raiz)
{
	if(!raiz)	
		return;
	NodoA *aux = raiz->izq;
	raiz->izq = raiz->dch;
	raiz->dch = aux;
	invertirRamas(raiz->izq);
	invertirRamas(raiz->dch);
}

void invertirArbol(Arbol *arbol)
{
	invertirRamas(arbol->raiz);
}

void buscarEnArbol(NodoA *raiz, void *dato, int *resultado,int (*comparar)(void*,void*))
{
	if(!raiz)
		return;
	buscarEnArbol(raiz->dch, dato, resultado, comparar);
	if(comparar(raiz->dato,dato) == 0)
		*resultado = 1;
	buscarEnArbol(raiz->izq, dato, resultado, comparar);
}

void guardarArbolEnPila(Arbol *arbol, Pila *pila)
{
	guardarNodoEnPila(arbol->raiz, pila);
}

void guardarNodoEnPila(NodoA *raiz, Pila *pila)
{
	if(!raiz)
		return;
	guardarNodoEnPila(raiz->dch,pila);
	guardarNodoEnPila(raiz->izq,pila);
	pushNodo(pila, raiz->dato);
}

int compararNodos(NodoA *raiz1, NodoA *raiz2,int(*comparar)(void*, void*))
{	
	return comparar(raiz1->dato,raiz2->dato);
}

int compararArbolesRec(NodoA *n1, NodoA *n2, int (*comparar)(void*, void*)) {
    if (!n1 && !n2) return 1; // ambos NULL → igual
    if (!n1 || !n2) return 0; // estructura distinta
    if (comparar(n1->dato, n2->dato) != 0) return -1; // datos distintos
    int izq = compararArbolesRec(n1->izq, n2->izq, comparar);
    int der = compararArbolesRec(n1->dch, n2->dch, comparar);
    if (izq == -1 || der == -1) return -1; // cualquier dato distinto → -1
    if (izq == 0 || der == 0) return 0;    // subestructura distinta pero mismos datos → 0
    return 1; // estructura y datos iguales
}

int compararArboles(Arbol arbol1, Arbol arbol2) {
    // primero revisamos cantidad de nodos
    if (arbol1.cantidad != arbol2.cantidad) return -1;

    int res = compararArbolesRec(arbol1.raiz, arbol2.raiz, arbol1.comparar);
    if (res == -1 || res == 1) return res; // datos distintos o todo igual

    // res == 0 → revisar si los mismos datos existen
    Pila *p1 = malloc(sizeof(Pila));
    *p1 = (Pila){NULL, 0, -1, NULL, NULL};

    guardarArbolEnPila(&arbol1, p1);

    while (p1->cima) {
        void *dato = p1->cima->dato;
        int encontrado = 0;
        buscarEnArbol(arbol2.raiz, dato, &encontrado, arbol1.comparar);
        if (!encontrado) {
            free(p1);
            return -1; // dato en arbol1 no encontrado en arbol2 → datos diferentes
        }
        popDato(p1);
    }

    free(p1);
    return 0; // mismos datos pero distinta estructura
}


void imprimirResultado(Resultado resultado)
{
	if(resultado.nodo)
	{
		if(resultado.padre)
		{
			printf("\n PADRE: ");
			imprimirEntero(resultado.padre);
			
		}
	}
}

NodoA* eliminarNodo(NodoA *raiz, void *dato, int (*comparar)(void*, void*), void (*liberar)(void*))
{
    if (!raiz) return NULL;

    int cmp = comparar(dato, raiz->dato);
	

    if (cmp < 0) {
        raiz->izq = eliminarNodo(raiz->izq, dato, comparar, liberar);
    } else if (cmp > 0) {
        raiz->dch = eliminarNodo(raiz->dch, dato, comparar, liberar);
    } else {
        // Nodo encontrado
        if (!raiz->izq) {
            NodoA *tmp = raiz->dch;
            free(raiz);
            return tmp;
        } else if (!raiz->dch) {
            NodoA *tmp = raiz->izq;
            free(raiz);
            return tmp;
        } else {
            // Nodo con dos hijos: reemplazar por el menor de la derecha
            NodoA *min = raiz->dch;
            while (min->izq) min = min->izq;
			void *datoMin = min->dato;
            raiz->dato = datoMin;
			
            raiz->dch = eliminarNodo(raiz->dch,datoMin, comparar, liberar);
        }
    }
    return raiz;
}

Arbol eliminarDatoEnArbol(Arbol arbol, void *dato, int (*comparar)(void*, void*))
{
    arbol.raiz = eliminarNodo(arbol.raiz, dato, comparar, arbol.liberar);
    arbol.cantidad--;  // actualizar cantidad
    return arbol;
}

void calcularProfundidad(NodoA *raiz, int nivel, int *profundidad)
{
	//Se queda con la profundidad mayor
	if(!raiz)
	{
		if(*profundidad < nivel-1)
			*profundidad = nivel - 1;
		return;
	}
	
	//Calcula la profundidad de la raiz derecha
	calcularProfundidad(raiz->dch,nivel+1,profundidad);
	
	//Calcula la profundidad de la raiz izquierda
	calcularProfundidad(raiz->izq,nivel+1,profundidad);
}

void profundidad(Arbol arbol)
{
	NodoA *raiz = arbol.raiz;
	
	int nivelDerecho = 0;
    int	nivelIzquierdo = 0;
	
	calcularProfundidad(raiz->dch,1,&nivelDerecho); //Calcula la profundidad de la raiz derecha del arbol
	
	calcularProfundidad(raiz->izq,1,&nivelIzquierdo); //Calcula la profundidad de la raiz izquierda del arbol
	
	printf("\n ND: %d",nivelDerecho);
	printf("\n NI: %d",nivelIzquierdo);
	printf("\n");
	int balance = nivelDerecho - nivelIzquierdo;
	
	if(balance > 1 || balance < -1)
		printf("\n Esta desbalanceado\n");
	else
		printf("\n Esta balanceado\n");
}

Arbol balancearArbol(Arbol arbol)
{
    if(!arbol.raiz) return arbol;

    void **arr = malloc(sizeof(void*) * arbol.cantidad);
    int index = 0;

    // Obtener elementos ordenados
    guardarEnArreglo(arbol.raiz, arr, &index);

    // Crear nuevo árbol
    Arbol nuevo;
    nuevo.raiz = construirBalanceado(arr, 0, arbol.cantidad - 1);
    nuevo.cantidad = arbol.cantidad;
    nuevo.imprimir = arbol.imprimir;
    nuevo.comparar = arbol.comparar;
    nuevo.liberar = arbol.liberar;

    free(arr);

    return nuevo;
}
void guardarEnArreglo(NodoA *raiz, void **arr, int *index)
{
    if(!raiz) return;

    guardarEnArreglo(raiz->izq, arr, index);
    arr[*index] = raiz->dato;
    (*index)++;
    guardarEnArreglo(raiz->dch, arr, index);
}

NodoA* construirBalanceado(void **arr, int inicio, int fin)
{
    if(inicio > fin) return NULL;

    int medio = (inicio + fin) / 2;

    NodoA *nodo = crearNodoA(arr[medio]);

    nodo->izq = construirBalanceado(arr, inicio, medio - 1);
    nodo->dch = construirBalanceado(arr, medio + 1, fin);

    return nodo;
}

void imprimirEntero(void *dato)
{
	int *datoE = dato;
	printf("%d", *datoE);
}

void imprimirCadena(void *dato)
{
	char *datoC = dato;
	printf(" %s", datoC);	
}



int compEntero( void *a,void *b)
{
	int *pA,*pB;
	pA = a;
	pB = b;
	return *pA - *pB;
}


int compCadenas( void *a,void *b)
{
	char *cadA,*cadB;
	cadA = a;
	cadB = b;
	return strcmp(cadA,cadB);
}





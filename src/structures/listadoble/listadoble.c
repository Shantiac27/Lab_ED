//ListaD.c 

#include "listadoble.h"

void insertarFinalD(ListaD *lista, void *dato)
{
	NodoD *nuevo = crearNodoD(dato);
	//LISTA VACIA
	if(!lista->inicio)
	{
		lista->inicio = lista->fin = nuevo;
	}
	//LISTA NO VACIA
	else
	{
		lista->fin->sig = nuevo;
		nuevo->ant = lista->fin;
		lista->fin = nuevo;
	}
	lista->cant++;
}


void imprimirListaDIF(ListaD lista)
{
	printf("\n [%d] LISTA", lista.cant);
	if(!lista.inicio)
	{
		printf("VACIA");
	}
	for(NodoD *aux = lista.inicio; aux != NULL; aux = aux->sig)
	{
		printf("\n");
		lista.imprimir(aux->dato);
	}
	
}


void imprimirListaDFI(ListaD lista)
{
	printf("\n [%d] LISTA", lista.cant);
	if(!lista.inicio)
	{
		printf("VACIA");
	}
	for(NodoD *aux = lista.fin; aux != NULL; aux = aux->ant)
	{
		printf("\n");
		lista.imprimir(aux->dato);
	}
	
}

void borrarInicioD(ListaD *lista)
{
	NodoD *aux;
	if(!lista->inicio)
		return;
	//UNICO NODO
	if(lista->inicio == lista->fin)
	{
		lista->inicio = lista->fin = NULL;
	}
	//MINIMO 2 NODOS
	aux = lista->inicio;
	lista->inicio = aux->sig;
	if(lista->liberar)
		lista->liberar(aux->dato);
	free(aux);
	lista->inicio->ant = NULL;
	
	lista->cant--;
}

void* removerInicio(ListaD *lista)
{
	if(!lista->inicio)
		return NULL;
	void *dato = lista->inicio->dato;
	lista->inicio->dato = NULL;
	borrarInicioD(lista);
	return dato;
}

void borrarListaD (ListaD *lista)
{
	//Comprobar si hay datos
	while(lista->inicio)
	{
		borrarInicioD(lista);
	}
}


void insertarEnOrden(ListaD *lista, void *dato)
{
	NodoD *nuevo = crearNodoD(dato);
	//LISTA VACIA?
	if ( !lista->inicio)
	{	
		lista->inicio = lista->fin = nuevo;
	}	
	//LISTA YA TIENE ALGO
	else
	{
		for (NodoD *q = NULL,*aux = lista->inicio; aux!= NULL ;q=aux, aux = aux->sig)
		{
			
			if( lista->comparar( nuevo->dato , aux->dato  ) < 0)
			{
				//REEMPLAZAR INICIO
				if(aux == lista->inicio)
				{
					nuevo->sig = aux;
					aux->ant = nuevo;
					lista->inicio = nuevo;
					lista->inicio->ant = NULL;
				}
				//INSERTAR EN MEDIO DE NODOS
				else
				{
					q->sig = nuevo;
					nuevo->ant = q;
					nuevo->sig = aux;
					aux->ant = nuevo;
				}
				break;
			}
			else if ( aux == lista->fin)
			{
				aux->sig = nuevo;
				nuevo->ant = aux;
				lista->fin = nuevo;
				break;
			}						
		}			
	}	
	lista->cant++;
}

void insertarInicioD(ListaD *lista, void *dato)
{
	NodoD *nuevo = crearNodoD(dato);
	
	//Lista vacia
	if(!lista->inicio)
	{
		lista->inicio = lista->fin = nuevo;
	}
	else
	{
		nuevo->sig = lista->inicio;
		lista->inicio->ant = nuevo;
		lista->inicio = nuevo;
		lista->inicio->ant = NULL;
		lista->cant++;
	}
}

int insertarEn(ListaD *lista, void *dato, int index)
{
	NodoD *nuevo = crearNodoD(dato);
	NodoD *aux = lista->inicio;
	NodoD *q = NULL;
	
	//El indice es mayor al rango
	if(index > lista->cant)
	{
		return 0;
	}
	//El indice se encuentra en el inicio
	else if(index == 1)
	{
		insertarInicioD(lista,dato);
		return 1;
	}
	//El indice esta dentro del rango
	else
	{
		for(int i = 0; i <= index - 1;q=aux, aux = aux->sig,i++)
		{
			if(i == index - 1)
			{
				q->sig = nuevo;
				nuevo->sig = aux;
				lista->cant++;
				return 1;
			}
		}
	}
	return -2;
}

int borrarEnD(ListaD *lista, int index)
{
	NodoD *aux = lista->inicio;
	NodoD *q = NULL;
	//El indice es mayor al rango
	if(index > lista->cant)
	{
		return 0;
	}
	//el indice se encuentra al inicio
	else if(index == 1)
	{
		borrarInicioD(lista);
		lista->cant--;
		return 1;
	}
	//El indice es igual al rango
	else if (index == lista->cant)
	{
		borrarFinD(lista);
		lista->cant--;
		return 1;
	}
	//El indice esta dentro del rango
	else
	{
		for(int i = 0; i <= index - 1;q=aux, aux = aux->sig,i++)
		{
			if(i == index - 1)
			{
				aux = aux->sig;
				q->sig = aux;
				aux->ant = q;
				lista->cant--;
				return 1;
			}
		}
	}
	return -2;
}

void borrarFinD(ListaD *lista)
{
	if(lista->inicio)
	{
		lista->fin->ant = lista->fin;
		lista->cant--;
	}
	
}
void borrarDatoD(ListaD *lista, void *dato)
{
	//el indice se encuentra al inicio
	if(lista->inicio->dato == dato)
	{
		borrarInicioD(lista);
		return;
	}
	//El dato se encuentra al final
	else if (lista->fin->dato == dato)
	{
		borrarFinD(lista);
		return;
	}
	//El indice esta dentro del rango
	else
	{
		for(NodoD *aux = lista->inicio, *q = NULL; aux != NULL ;q=aux, aux = aux->sig)
		{
			if(aux->dato == dato)
			{
				aux = aux->sig;
				q->sig = aux;
				aux->ant = q;
				lista->cant--;
				return;
			}
		}
	}
}
void reordenar (ListaD *lista, int (*comparar) (void*, void*))
{
	ListaD aux = {NULL,NULL,0,lista->imprimir,comparar,lista->liberar};
	void *dato;
	while( lista->cant)
	{
		dato = removerInicio(lista);
		insertarEnOrden(&aux,dato);		
	}
	*lista = aux;
}

Resultado buscar(ListaD lista,void *dato)
{	
	Resultado resultado = {NULL,NULL,NULL};
	for (NodoD *q = NULL,*p = lista.inicio; p!= NULL ;q=p, p = p->sig)
	{
		if( lista.comparar(dato, p->dato) == 0)
		{
			//LO ENCONTRAMOS
			resultado.ante = q;
			resultado.enco = p;
			resultado.dato = p->dato;
			break;
		}
	}
	return resultado;
}

void imprimirResultado(ListaD lista,Resultado res)
{
	
	if( res.enco )
	{
		//ENCONTRADO
		if(res.ante)
		{
			printf("\n Anterior:" );
			lista.imprimir(res.ante->dato);
		}
		printf("\n Encontrado:" );
		lista.imprimir(res.enco->dato);
	}
	else
	{
		//NO ENCONTRADO
		printf("\n No encontrado");
	}
}
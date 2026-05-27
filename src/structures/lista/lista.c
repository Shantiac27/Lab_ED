//LISTA.c
#include "Lista.h"

void agregarFinal(Lista *lista,void *dato)
{
	Nodo *nuevo = crearNodo(dato);
	//LISTA VACIA
	if( lista->inicio==NULL && lista->inicio==lista->fin)
	{
		//AGREGAR UNICO NODO
		lista->inicio = lista->fin = nuevo;		
	}
	//LISTA TIENE MINIMO UN NODO
	else
	{
		//ENLAZAR NODO AL FINAL
		lista->fin->sig = nuevo;
		//ACTUALIZAR FINAL
		lista->fin = nuevo;
	}
	lista->cantidad++;
}


Resultado buscar(Lista lista,void *dato)
{	
	Resultado resultado = {NULL,NULL,NULL};
	for (Nodo *q = NULL,*p = lista.inicio; p!= NULL ;q=p, p = p->sig)
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



void imprimirResultado(Lista lista,Resultado res)
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

void agregarEnOrden(Lista *lista,void *dato)
{
	Nodo *nuevo = crearNodo(dato);
	//LISTA VACIA?
	if ( !lista->inicio)
	{	
		lista->inicio = lista->fin = nuevo;
	}	
	//LISTA YA TIENE ALGO
	else
	{
		for (Nodo *q = NULL,*aux = lista->inicio; aux!= NULL ;q=aux, aux = aux->sig)
		{
			
			if( lista->comparar( nuevo->dato , aux->dato  ) < 0)
			{
				//REEMPLAZAR INICIO
				if(aux == lista->inicio)
				{
					nuevo->sig = aux;
					lista->inicio = nuevo;
				}
				//INSERTAR EN MEDIO DE NODOS
				else
				{
					q->sig = nuevo;
					nuevo->sig = aux;
				}
				break;
			}
			else if ( aux == lista->fin)
			{
				aux->sig = nuevo;
				lista->fin = nuevo;
				break;
			}						
		}			
	}	
	lista->cantidad++;
}

void imprimirLista(Lista lista)
{
	//SALIR DE LA FUNCION SI LA LISTA ESTA VACIA
	printf("\n\n [%d] LISTA : \n",lista.cantidad); 
	if(!lista.inicio)
	{
		printf(" VACIA\n");
		return;
	}
	//RECORRER NODOS HASTA QUE LLEGUE EL
	//ENLACE SIGUENTE DEL ULTIMO NODO, QUE ES NULO
	for ( Nodo *aux = lista.inicio; aux!= NULL ; aux = aux->sig)
	{
		//UTILIZAR LA FUNCION DE IMPRIMIR ESPECIFICADA
		//EN LA LISTA
		lista.imprimir( aux->dato );
		//LA FUNCION SE ENCARGA DE DESREFERENCIAR
		//LA DIRECCION DE TIPO VOID AL TIPO ESPECIFICO
	}	
	printf("\n");
}






void eliminarInicio(Lista *lista)
{
	Nodo *aux;
	if(lista->inicio)
	{
		aux = lista->inicio;
		lista->inicio = aux->sig;
		//ELIMINASTE EL UNICO NODO
		if( !lista->inicio) //lista->inicio == NULL
			lista->fin = NULL;
		lista->cantidad--;
		free(aux);
	}
}

void eliminarFinal(Lista *lista)
{
	if(lista->inicio)
	{	
		Resultado res = buscar(*lista,lista->fin->dato);
		lista->fin = res.ante; //PENULTIMO
		if(lista->fin)
			lista->fin->sig = NULL;
		else 
			lista->inicio = NULL;
		free(res.enco); //FIN
		lista->cantidad--;
	}	
}


void eliminarDato(Lista *lista,void *dato)
{
	Resultado res = buscar(*lista,dato);
	if( res.enco)
	{
		if( res.enco == lista->inicio)
			eliminarInicio(lista);
		else if (res.enco == lista->fin)
			eliminarFinal(lista);
		else
		{
			res.ante->sig = res.enco->sig;
			if(lista->liberar)lista->liberar(res.enco->dato);
			free(res.enco);
			lista->cantidad--;
		}
	}
}

void insertarInicio(Lista *lista, void *dato)
{
	Nodo *nuevo = crearNodo(dato);
	
	//Lista vacia
	if(!lista->inicio)
	{
		lista->inicio = lista->fin = nuevo;
	}
	else
	{
		nuevo->sig = lista->inicio;
		lista->inicio = nuevo;
	}
	lista->cantidad++;
}

int insertarEn(Lista *lista, void *dato, int index)
{
	Nodo *nuevo = crearNodo(dato);
	Nodo *aux = lista->inicio;
	Nodo *q = NULL;
	
	//El indice es mayor al rango
	if(index > lista->cantidad)
	{
		return 0;
	}
	//El indice se encuentra en el inicio
	else if(index == 1)
	{
		insertarInicio(lista,dato);
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
				lista->cantidad++;
				return 1;
			}
		}
	}
	return -2;
}



int eliminarEn(Lista *lista, int index)
{
	Nodo *aux = lista->inicio;
	Nodo *q = NULL;
	//El indice es mayor al rango
	if(index > lista->cantidad)
	{
		return 0;
	}
	//el indice se encuentra al inicio
	else if(index == 1)
	{
		eliminarInicio(lista);
		return 1;
	}
	//El indice es igual al rango
	else if (index == lista->cantidad)
	{
		eliminarFinal(lista);
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
				lista->cantidad--;
				return 1;
			}
		}
	}
	return -2;
}

void* removerInicio(Lista *lista)
{
	if(!lista->inicio)
		return NULL;
	void *dato = lista->inicio->dato;
	lista->inicio->dato = NULL;
	eliminarInicio(lista);
	return dato;
}

void reordenar(Lista *lista, int (*comparar)(void*,void*))
{
	Lista aux = {NULL,NULL,0,lista->imprimir,comparar,lista->liberar};
	void *dato;
	while( lista->cantidad  )
	{
		dato = removerInicio(lista);
		agregarEnOrden(&aux,dato);		
	}
	*lista = aux;
	
}
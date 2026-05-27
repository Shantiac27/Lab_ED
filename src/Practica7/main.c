
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <iostring.h>
#include <arbol.h>
#include <stdbool.h>
#include "variable.h"
#include "expresion.h"

#define IZQ 0
#define DEC 1

void abortar(void);
void ordenIterativo(NodoA *raiz,void (*imprimir)(void*));
void imprimirDoubleDouble(void *);

Arbol arbolPostfix(char *postfix);

int verificarParentesis(char *cadena);
char* cadenaSinEspacios(char *cadena);
char* volverPostfix(char* infix);
int valorCaracter(char c);

bool esOperando(char caracter);

int main(void)
{
	Arbol arbol;
	arbol.raiz = NULL;
	arbol.imprimir = &imprimirVariable;
	arbol.comparar = &compararVariable;
	arbol.liberar = &free;
	
	int opcion = 0;
	
	char expresion[20];
	
	char* postfix;
	
	//NOTA
	/*arbol.cantidad = 7; // <<-- ACTUALIZAR ESTE VALOR SI SE CREA MANUALMENTE EL ARBOL	
	arbol.raiz = crearNodoA(crearVariable('^'));	
	arbol.raiz->izq = crearNodoA(crearVariable('X'));	
	arbol.raiz->dch = crearNodoA(crearVariable('^'));	
	arbol.raiz->dch->izq = crearNodoA(crearVariable('X'));	
	arbol.raiz->dch->dch = crearNodoA(crearVariable('^'));	
	arbol.raiz->dch->dch->izq = crearNodoA(crearVariable('X'));	
	arbol.raiz->dch->dch->dch = crearNodoA(crearVariable('Y'));	*/
	
	while(opcion != 3)
	{
		printf("\n\n");
		printf("\n EXPRESION: ");
	    printf("\n [0] CAPTURAR EXPRESION");
	    printf("\n [1] IMPRIMIR ARBOL DE EXPRESION");
	    printf("\n [2] EVALUAR EXPRESION");
		printf("\n [3] TERMINAR PROGRAMA");
		printf("\nQue deseas hacer: ");
		scanf("%d",&opcion);
	
	    switch(opcion)
	    {
		    case 0:
			{
		      printf("\n ESCRIBA UNA EXPRESION: ");
			  scanf("%s", expresion);
			  
			  if(verificarParentesis(expresion) == 1)
			  {
				  printf("\n EXPRESION CORRECTA");
				  printf("\n IMPRIMIENDO ARBOL DE EXPRESION...");
				  
				  postfix = volverPostfix(expresion);
				  
				  arbol = arbolPostfix(postfix);
				  
				  printf("\n ARBOL DE EXPRESION LISTO");
			  }
			  else
			  {
				  printf("\n EXPRESION NO VALIDA");
			  }
			}
			break;
			
		    case 1:
			{
		        imprimirArbol(arbol);
			}
			break;
			
		    case 2:
			{
				evaluar(arbol);
			}
			break;
			
		    case 3:
		    break;
		
		    default:
			printf("\nOpcion invalida");
		    break;
		
	    }
	}
	
	/*printf("\n ARBOL\n");
	imprimirArbol(arbol);
	evaluar(arbol);*/

	
	
	eliminarArbol(&arbol);

	printf("\n\n FIN DE PROGRAMA\n");
	
	
	return 0;
}


void imprimirDoubleDouble(void *ptr)
{
	double **ptrdouble= ptr;	
	if(!ptrdouble)	
	{		
		printf("null ") ;
		return;
	}
	printf("%lf ",**ptrdouble); 
}

void ordenIterativo(NodoA *raiz,void (*imprimir)(void*))
{
	Pila pila = {NULL,0,-1,imprimir,NULL};
	if(!raiz)
		return;
	NodoA* aux = raiz;
	while( aux || !pilaVacia(pila))
	{			
		while(aux)
		{
			pushDato(&pila,aux);	
			aux = aux->izq;
		}		
		aux = popDato(&pila);
		imprimir(aux);		
		printf(" ");		
		aux= aux->dch;
	}	
	vaciarPila(&pila);
}

void abortar(void)
{
	char c = 'e';
	if( (c=getchar()) == 'e')
		exit(0);
}

Arbol arbolPostfix(char *postfix)
{
	if(!postfix)
	{
		Arbol a = {0};
		
		return a;
	}
	
	Arbol arbol;
	arbol.raiz = NULL;
	arbol.cantidad = 0;
	arbol.imprimir = &imprimirVariable;
	arbol.comparar = &compararVariable;
	arbol.liberar = &free;
	
	Pila pila = {NULL,0,-1,NULL,NULL};
	
	int i = 0;
	
	while(postfix[i] != '\0')
	{
		char caracter = postfix[i];
		
		if(esOperando(caracter))
		{
			pushDato(&pila, crearNodoA(crearVariable(caracter)));
			arbol.cantidad++;
		}
		else
		{
			NodoA* nodo = crearNodoA(crearVariable(caracter));
			nodo->dch = (NodoA*) popDato(&pila);
			nodo->izq = (NodoA*) popDato(&pila);
			pushDato(&pila,nodo);
			
			arbol.cantidad++;
		}
		
		i++;
	} 
	
	arbol.raiz = (NodoA*) popDato(&pila);
	
	vaciarPila(&pila);
	
	return arbol; 
}

char* cadenaSinEspacios(char *cadena)
{
	int largo = strlen(cadena);
	
	char *nuevaCadena = malloc(largo+1);
	
	if(nuevaCadena == NULL)
		return NULL;
	
	int cont = 0;
	for(int i = 0; i < largo; i++)
	{
		if(cadena[i] != ' ')
		{
		    nuevaCadena[cont] = cadena[i];
			cont++;
		}
	}
	
	nuevaCadena[cont] = '\0';
	
	return nuevaCadena;
}

int valorCaracter(char c)
{
	switch(c)
	{
		case '(':
			return -1;
		break;
		
		case '+':
		case '-':
			return 1;
		break;
		
		case '/':
		case '*':
			return 2;
		break;
		
		case '^': 
			return 3;
		break;
		
		case ')':
			return 4;
		break;
		
		default:
			return 0;
		break;
	}
	
	return 0;
	
	
}

bool esOperando(char caracter)
{
	if((caracter >= 65 && caracter <= 90) ||
		(caracter >= 97 && caracter <= 122))
		return true;
		
	return false;
}

char* volverPostfix(char* infix)
{
	if(infix == NULL) return NULL;
	
	int largo = strlen(infix);
	
	char *postfix = malloc(largo+1);
	
	Pila pila = {NULL,0,-1,NULL,NULL};
	
	int i = 0; //Contador de la cadena infix
	int p = 0; //Contador de la cadena postfix
	
	while(infix[i] != '\0')
	{
		char caracter = infix[i];
		
		char* nuevo = malloc(sizeof(char));
		*nuevo = caracter;
		
		int nivel = valorCaracter(caracter);
		
		
		if(nivel == -1)// '('
		{
			pushDato(&pila,nuevo);
		}
		else if(caracter == ')') // ')'
		{
			while(pila.cima && valorCaracter(*(char*)pila.cima->dato) != -1)
			{
				postfix[p++] = *(char*)popDato(&pila);
			}
			if(pila.cima) popDato(&pila);
		}
		else if(nivel == 0)//Es un operando
		{
			postfix[p++] = caracter;
		}
		else if(nivel == 1)// + y -
		{
			while(pila.cima && valorCaracter(*(char*)pila.cima->dato) >= 1)
			{
				postfix[p++] = *(char*)popDato(&pila);
			}
			pushDato(&pila,nuevo);
		}
		else if(nivel == 2)// * y /
		{
			while(pila.cima && valorCaracter(*(char*)pila.cima->dato) >= 2)
			{
				postfix[p++] = *(char*)popDato(&pila);
			}
			pushDato(&pila,nuevo);
		}
		else if(nivel == 3)// ^
		{
			while(pila.cima && valorCaracter(*(char*)pila.cima->dato) > 3)
			{
				postfix[p++] = *(char*)popDato(&pila);
			}
			pushDato(&pila,nuevo);
		}
		
		i++;
	}
	
	while(pila.cima)
	{
		postfix[p++] = *(char*)popDato(&pila);
	}
	
	postfix[p] = '\0';
	
	return postfix;
}

int verificarParentesis(char *cadena)
{
	Pila pila = {NULL,0,-1,NULL,NULL};
	
	int i = 0;
	
	while(cadena[i] != '\0')
	{
		char caracter = cadena[i];
        if(caracter == '{' || caracter == '[' || caracter == '(')
		{
			pushDato(&pila,&cadena[i]);
		}			
		else if(caracter == '}' || caracter == ']' || caracter == ')')
		{
			if(!pila.cima)
			{
				return 0;
			}
			else
			{
				char tope = *(char*) pila.cima->dato;
				if(tope == '{' && caracter == '}')
				{
					popDato(&pila);
				}
				else if(tope == '[' && caracter == ']')
				{
					popDato(&pila);
				}
				else if(tope == '(' && caracter == ')')
				{
					popDato(&pila);
				}
				else
				{
					return 0;
				}
			}
		}
	    i++;
	}
	
	return (pila.cima == NULL);
	
}
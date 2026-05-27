//Practica 3

#include <stdio.h>
#include <iostring.h>
#include <String.h>
#include <pila.h>


#define MAX 100

int palindromo(char *cadena);

int verificarParentesis(char *cadena);

char* cadenaSinEspacios(char *cadena);

int main()
{
	char *cadena = NULL;
	
	inputCadenaDinamica("\n Captura cadena: ",&cadena,MAX);
	printf(" Es palindromo: %s", palindromo(cadena) ? "SI" : "NO");
	
	inputCadenaDinamica("\n\n Captura expresion: ",&cadena,MAX);
	printf(" Parentesis correctos : %s", verificarParentesis(cadena) ? "SI" : "NO");
	
	free(cadena);
	printf("\n\n FIN DE PROGRAMA");
	return 0;
	
}


int palindromo(char *cadena)
{
	Pila pila = {NULL,0,-1,NULL,NULL};
	
	cadena = cadenaSinEspacios(cadena);
	
	int largo = strlen(cadena);
	
	for(int i = 0; i < largo/2; i++)
	{
		pushDato(&pila,&cadena[i]);
		char tope = *(char*)pila.cima->dato;
	    if(tope != cadena[largo - 1 - i])
	    {
		    return 0;
	    }
		
	}
	return 1;	
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
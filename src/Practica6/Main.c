//infix.h

#include <stdio.h>
#include <stdlib.h>
#include <pila.h>
#include <iostring.h>
#include <string.h>

int verificarParentesis(char *cadena);
char* cadenaSinEspacios(char *cadena);
char* volverPostfix(char* infix);

int main(void)
{
  char *cadena = malloc(100 * sizeof(char));
  char *postfix;
  
  printf("\nCadena: ");
  scanf("%s", cadena);
  
  if(verificarParentesis(cadena) != 0)
  {
	  printf("\nTransformando a postfix....");
	  postfix = volverPostfix(cadena);
	  printf("\nCadena postfix: %s", postfix);
  }
  else
	  printf("\nCadena no cumple los criterios");
  
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

/*char* volverPostfix(char* infix)
{
	if(infix == NULL) return NULL;
	
	int largo = strlen(infix);
	
	char *postfix = malloc(largo+1);

	Pila pila = {NULL,0,-1,NULL,NULL};
	
	int i = 0; //contador de la cadena infix
	int p = 0; //contador de la cadena postfix
	
	while(infix[i] != '\0' && infix != NULL)
	{
		char caracter = infix[i];
		
		switch(caracter)
		{
			case '+':
			case '-':
			{
				while(pila.cima && *(char*)pila.cima->dato != '(')
				{
					postfix[p++] = *(char*)popDato(&pila);
				}
				pushDato(&pila,&caracter);
			}
		    break;
			
		    case '*':
			case '/':
			{ 
			   while(pila.cima && (*(char*)pila.cima->dato != '(' && 
			                        *(char*)pila.cima->dato != '+' &&
									*(char*)pila.cima->dato != '-'))
				{
					postfix[p++] = *(char*)popDato(&pila);
				}
				pushDato(&pila,&caracter);
			}
			break;
			
			case '^':
		    {
			    while(pila.cima && (*(char*)pila.cima->dato == '^' && *(char*)pila.cima->dato != '('))
			    {
				    postfix[p++] = *(char*)popDato(&pila);
			    }
				pushDato(&pila,&caracter);
			}
			break;
			
			case '(':
					
				pushDato(&pila,&caracter);
				
			break;
			
			case ')':
			{
				while(pila.cima && *(char*)pila.cima->dato != '(')
			    {
				    postfix[p++] = *(char*)popDato(&pila);
			    }
				if(pila.cima) {
					char *dato = popDato(&pila);
					free(dato);
				} else {
					printf("Error: parentesis desbalanceados\n");
				}
			}
			break;
				
			default:
			postfix[p++] = caracter;
			
			break;
		}
		
		i++;
	}
	
	while(pila.cima)
	{
		postfix[p++] = *(char*)popDato(&pila);
	}
	
	postfix[p] = '\0';
	
	return postfix;
}*/



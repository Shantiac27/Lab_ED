//Main

#include <stdio.h>
#include <stdlib.h>
#include "../iostring/iostring.h"
#include "../structures/listadoble/listadoble.h"
#include "alumno.h"
#include <string.h>

void imprimirEntero(void *dato);
void imprimirCadena(void *dato);

int compEntero( void *a,void *b);
int compCadenas( void *a,void *b);


int main()
{
	ListaD lista = {NULL,NULL,0,imprimirAlumno,compararMatricula,free};
	int opcion;
	int opcion2;
	
	
	while(opcion != 6)
	{
		printf("\n\n");
	    printf("\n1. Registrar alumno");
	    printf("\n2. Desplegar alumnos");
	    printf("\n3. Reordenar la lista");
	    printf("\n4. Buscar alumno");
	    printf("\n5. Borrar alumno");
	    printf("\n6. Salir del sistema");
		printf("\nQue deseas hacer:");
		scanf("%d",&opcion);
	
	    switch(opcion)
	    {
		    case 1:
			{
		        Alumno *alumno; 
			    alumno = crearAlumno();
				if(alumno == NULL)
					break;
				printf("Alumno creado correctamente");
                insertarEnOrden(&lista,alumno);
			
		        break;
			}
		    case 2:
			{
				imprimirListaDFI(lista);
		        break;
			}
		    case 3:
			
			printf("\n1.Por matricula");
			printf("\n2.Por orden alfabetico");
			printf("\n3.Por semestres cursados");
			printf("\n4.Por promedio");
			printf("\nDe que manera quieres reordenar la lista: ");
			scanf("%d",&opcion2);
			
			switch(opcion2)
			{
				case 1:
				reordenar(&lista,compararMatricula);
				break;
				
				case 2:
				reordenar(&lista,compararNombre);
				break;
				
				case 3:
				reordenar(&lista,compararSemestre);
				break;
				
				case 4:
				reordenar(&lista,compararPromedio);
				break;
				
				default:
				printf("Opcion invalida");
				break;
			}
			printf("\nLista Reordenada");
		
		    break;
		
		    case 4:
			{
			    printf("\nMatricula a buscar: ");
				int mat;
				scanf("%d",&mat);
				Resultado res = buscar(lista,&mat);
				if(res.enco)
				{
					imprimirResultado(lista,res);
				}
				else
				{
					printf("\nAlumno no encontrado");
				}
			}
		    break;
		
		
		    case 5:
			{
				printf("\nMatricula a buscar: ");
			    int mat;
				scanf("%d",&mat);
				Resultado res = buscar(lista,&mat);
				if(res.enco)
				{
					borrarDatoD(&lista,res.dato);
					printf("\nAlumno eliminado");
				}
				else
				{
					printf("\nAlumno no encontrado");
				}
			}
		    break;
		
		    case 6:
		
		    break;
		
		    default:
			printf("\nOpcion invalida");
		    break;
		
	    }
	}
	
}

void imprimirEntero(void *dato)
{
	int *datoE = dato;
	printf(" %d", *datoE);
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostring.h>
#include <arbol.h>


int main(void)
{
    Arbol arbolA = {NULL, 0, imprimirEntero, compEntero, free};
    Arbol arbolB = {NULL, 0, imprimirEntero, compEntero, free};
	
	int opcion = 0;
	
	int num[9];
	int num2[9];
	
	num[0] = 8; insertarArbol(&arbolA, &num[0]);
	num[1] = 7; insertarArbol(&arbolA, &num[1]);
	num[2] = 10; insertarArbol(&arbolA, &num[2]);
	num[3] = 6; insertarArbol(&arbolA, &num[3]);
	num[4] = 4; insertarArbol(&arbolA, &num[4]);
	num[5] = 1; insertarArbol(&arbolA, &num[5]);
	num[6] = 5; insertarArbol(&arbolA, &num[6]);
	num[7] = 9; insertarArbol(&arbolA, &num[7]);
	num[8] = 11; insertarArbol(&arbolA, &num[8]);
	
	num2[0] = 7; insertarArbol(&arbolB, &num2[0]);
	num2[1] = 5; insertarArbol(&arbolB, &num2[1]);
	num2[2] = 4; insertarArbol(&arbolB, &num2[2]);
	num2[3] = 6; insertarArbol(&arbolB, &num2[3]);
	num2[4] = 1; insertarArbol(&arbolB, &num2[4]);
	num2[5] = 10; insertarArbol(&arbolB, &num2[5]);
	num2[6] = 9; insertarArbol(&arbolB, &num2[6]);
	num2[7] = 11; insertarArbol(&arbolB, &num2[7]);
	num2[8] = 8; insertarArbol(&arbolB, &num2[8]);
	
	while(opcion != 9)
	{
		printf("\n\n");
	    printf("\n1. Insertar en arbol A");
	    printf("\n2. Insertar en arbol B");
	    printf("\n3. Comparar arboles");
	    printf("\n4. Eliminar dato en Arbol A");
	    printf("\n5. Eliminar dato en Arbol B");
	    printf("\n6. Profundidades");
		printf("\n7. Equilibrar arboles");
		printf("\n8. Mostrar arboles");
		printf("\n9. Salir del sistema");
		printf("\nQue deseas hacer:");
		scanf("%d",&opcion);
	
	    switch(opcion)
	    {
		    case 1: 
			{
				int *newDato = malloc(sizeof(int));
				printf("\nInserte nuevo dato al arbol: ");
				scanf("%d", newDato);
				insertarArbol(&arbolA, newDato);
			}
			break;

			case 2: {
				int *newDato = malloc(sizeof(int));
				printf("\nInserte nuevo dato al arbol: ");
				scanf("%d", newDato);
				insertarArbol(&arbolB, newDato);
			}
            break;
		    case 3:
		    {
				printf("\nComparando arboles...");
                int comparacion = compararArboles(arbolA, arbolB);
				if(comparacion == -1)
					printf("\n Arboles distintos");
				else if(comparacion == 0)
					printf("\n Arboles con mismos datos, distinta estructura");
				else if(comparacion == 1)
					printf("\n Arboles iguales");
			}
		    break;
		
		    case 4:
			{
			    int new;
				printf("\nDato que quiere eliminar: ");
				scanf("%d",&new);
				int buscar = 0;
				buscarEnArbol(arbolA.raiz,&new,&buscar,arbolA.comparar);
				if(buscar == 0)
				{
					printf("\n Dato no se encuentra en el arbol");
                    break;					
				}
				arbolA = eliminarDatoEnArbol(arbolA,&new,arbolA.comparar);
				printf("\n Dato eliminado");
			}
		    break;
		
		
		    case 5:
			{
				int new;
				printf("\nDato que quiere eliminar: ");
				scanf("%d",&new);
				int buscar = 0;
				buscarEnArbol(arbolB.raiz,&new,&buscar,arbolB.comparar);
				if(buscar == 0)
				{
					printf("\n Dato no se encuentra en el arbol");
                    break;
				}
				arbolB = eliminarDatoEnArbol(arbolB,&new,arbolB.comparar);
				printf("\n Dato eliminado");
			}
		    break;
		
		    case 6:
			{
				printf("\nArbol A");
				profundidad(arbolA);
				printf("\nArbol B");
				profundidad(arbolB);
			}
		    break;
		    
			case 7:
			{
				arbolA = balancearArbol(arbolA);
				arbolB = balancearArbol(arbolB);
				printf("\nArboles balanceados\n");
			}
			break;
			
			case 8:
			{
				printf("\nArbol A\n");
				imprimirArbol(arbolA);
				printf("\nArbol B\n");
				imprimirArbol(arbolB);
			}
			break;
			
			case 9:
			break;
		    default:
			printf("\nOpcion invalida");
		    break;
		
	    }
	}

    imprimirOrden(arbolA,4);
	printf("\n");
	imprimirOrden(arbolB,4);
	printf("\n\n FIN DE PROGRAMA\n");
	
	
	return 0;
}


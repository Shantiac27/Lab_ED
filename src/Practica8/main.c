#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <iostring.h>
#include <heap.h>

int* crearEntero(int);
int compararEntero(void*,void*);
void imprimirEntero(void*);


int main(void)
{
	Heap heap = crearHeap(HEAP_MIN,compararArchivo,imprimirArchivo);
	
	int opcion = 0;
	
	while(opcion != 6)
	{
		printf("\n\n");
		printf("\n FILA DE IMPRESION: ");
	    printf("\n [0] CAMBIAR PRIORIDAD");
	    printf("\n [1] MOSTRAR COLA DE IMPRESION");
	    printf("\n [2] AGREGAR ARCHIVO");
		printf("\n [3] PROCESAR ARCHIVO");
		printf("\n [4] ELIMINAR ARCHIVO");
		printf("\n [5] ELIMINAR TODOS LOS ARCHIVOS");
		printf("\n [6] TERMINAR PROGRAMA");
		printf("\nQue deseas hacer: ");
		scanf("%d",&opcion);
	
	    switch(opcion)
	    {
		    case 0:
			{
				cambiarPrioridad(&heap);
			}
			break;
			
		    case 1:
			{
		        imprimirHeap(heap);
				imprimirHeapArbol(heap);
			}
			break;
			
		    case 2:
			{
				char nombre[100];
				int paginas;
				
				printf("\nNOMBRE DEL ARCHIVO: ");
				scanf("%s", nombre);
				printf("\nCANTIDAD DE PAGINAS: ");
				scanf("%d", &paginas);
				insertarHeap(&heap, crearArchivo(nombre, paginas));
				printf("\nARCHIVO INGRESADO A LA COLA DE IMPRESION");
			}
			break;
			
		    case 3:
			{
				Archivo *archivo;
				archivo = eliminarHeap(&heap);
				printf("\nARCHIVO PROCESADO: ");
				heap.imprimir(archivo);
			}
		    break;
			
			case 4:
			{
				int indice;
				imprimirHeap(heap);
				printf("QUE ARCHIVO DESEA  ELIMINAR: ");
				scanf("%d", &indice);
				free(eliminarDatoHeap(&heap, indice));
				printf("\nARCHIVO ELIMINADO");
			}
			break;
			
			case 5:
			{
				destruirHeap(&heap);
				printf("COLA DE IMPRESION ELIMINADA");
			}
			break;
			
			case 6:
			break;
		
		    default:
			printf("\nOpcion invalida");
		    break;
		
	    }
	}
	
	
	destruirHeap(&heap);

	printf("\n\n FIN DE PROGRAMA\n");
	
	
	return 0;
}

#include <stdio.h>
#include <stdlib.h>

#include "Laberinto.h"




int main(void)
{
    Laberinto lab = crear_laberinto();
	Coordenada origen = {1,1};
	Coordenada destino = {25,24};
	Pila movimientos = {NULL,0,-1,NULL,NULL};
	Movimientos invalido = {0,0,0,0};
	setOrigen(lab,origen);
	setDestino(lab,destino);
	imprimirLab(lab);
	
	pushDato(&movimientos,&origen);
	Coordenada *cima = movimientos.cima->dato;
	
	while(!pilaVacia(movimientos) && !(compararCoordenada(cima,&destino)))
	{
		if(!compararMovimientos(movimientosPosibles(lab,*cima),invalido))
		{
			moverseEnLaberinto(lab,&movimientos);
		}
		else
		{
			if(!compararMovimientos(regresosPosibles(lab,*cima),invalido))
			{
				regresar(lab,&movimientos);
			}
		}
		cima = movimientos.cima->dato;
	}
	
    imprimirLab(lab);
	liberarLaberinto(lab);
    printf("\n\n FIN DE PROGRAMA\n\n");
    return 0;
}


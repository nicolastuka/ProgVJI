#include "Scene.h"

int main() {
	srand(time(0));//fijate que le paso como parametro la funcion time de C para que me traiga como valor el tiempo actual
	//srand digamos que es un generador de semillas para "generacion" de numeros aleatorios.


	//bueno una vez que planto la semilla como se dice en la jerga inicio el programa.
	//ahora le quite el comentario asi vez como varia el valor o los valores
	//perfecto, seguimos...
	new Scene(142 * 3, 350, "Promedio de Puntajes");//en este caso creo una instancia de la clase Scene pero no 
	//guardo referencia a ella en ninguna variable... lo que digo es que cree una escena y le paso los valores para la
	//ventana que va a crear
	return 0;
}
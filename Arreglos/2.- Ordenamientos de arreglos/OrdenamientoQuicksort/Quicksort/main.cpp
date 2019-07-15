#include <iostream>

/*
	Los comentarios de este código los leemos de forma ordenada. Recuerden que aquí hay que dividir no el vector
	pero si su tratamiento en partes. Este algoritmo resulta ideal para grandes cantidades de datos.
*/

using namespace std;

/*
	2.- Aquí se observa que la función recibe un arreglo, un valor que indica el índice inicial desde la izquierda y 
	el último indica el índice final o desde la derecha
*/
void Quicksort(int *arreglo, int izquierda, int derecha) {
	int i = izquierda;//almaceno el límite de la izquierda
	int j = derecha;//y aqui en este caso el de la derecha
	int temporal;//esta variable la vamos a usar luego
	//Así determinamos y recordamos cual es el pivot para dividir la tarea de ordenamiento
	int pivot = arreglo[(izquierda + derecha) / 2];

	cout << "Pivot -->" << pivot << endl;

	//mientras el valor actual de límite izquierdo sea menor o igual al límite derecho
	while (i <= j) {
		//mientras el valor en la posición i sea menor que el pivot que encontramos antes
		while (arreglo[i] < pivot) {
			i++;//incrementamos el límite izquierdo
		}
		//mientras el valor en la posición j sea mayor que el pivot que encontramos antes
		while (arreglo[j] > pivot) {
			j--;//decrementamos el valor de j
		}
		//fíjense como los límites empiezan a acercarse entre sí luego de los while anteriores.

		//si se sigue cumpliendo la condición inicial
		if (i <= j) {
			//momento de realizar los intercambios
			temporal = arreglo[i];
			arreglo[i] = arreglo[j];
			arreglo[j] = temporal;
			//nuevamente se acercan los límites
			i++;
			j--;
		}
	}

	//Cuando ya i y j han excedido sus límites realizamos comparaciones

	if (izquierda < j) {
		/*
			La función se llama así misma pero en esta ocasión, ya no trabaja sobre todo el arreglo.
			En este caso, se pasa el arreglo que se recibió, el límite izquierdo y como límite derecho 
			el valor obtenido en J. Se llamará así mismo, buscará su pivot nuevamente, etc.
		*/
		Quicksort(arreglo, izquierda, j);
	}
	if (i < derecha) {
		/*
			Análogamente al IF anterior pero mirando el otro lado del arreglo
		*/
		Quicksort(arreglo, i, derecha);
	}
}

int main() {

	int valores[] = { -1, 1, 2, -2, 0 };

	cout << "Valores desordenados:" << endl;
	for (int i = 0; i < 5; i++) {
		cout << valores[i] << endl;
	}

	/*
		1.- Necesito trabajar este algoritmo aplicando recursividad (se llama a sí mismo), por eso lo hago en una función.
		Sus parámetros son el vector a manipular, la posición inicial y la posición final de nuestros elementos
	*/
	Quicksort(valores, 0, 4);

	cout << "Valores ordenados:" << endl;
	for (int i = 0; i < 5; i++) {
		cout << valores[i] << endl;
	}

	getchar();
	return 0;
}
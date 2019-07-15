#include <iostream>

/*
	Los comentarios de este c�digo los leemos de forma ordenada. Recuerden que aqu� hay que dividir no el vector
	pero si su tratamiento en partes. Este algoritmo resulta ideal para grandes cantidades de datos.
*/

using namespace std;

/*
	2.- Aqu� se observa que la funci�n recibe un arreglo, un valor que indica el �ndice inicial desde la izquierda y 
	el �ltimo indica el �ndice final o desde la derecha
*/
void Quicksort(int *arreglo, int izquierda, int derecha) {
	int i = izquierda;//almaceno el l�mite de la izquierda
	int j = derecha;//y aqui en este caso el de la derecha
	int temporal;//esta variable la vamos a usar luego
	//As� determinamos y recordamos cual es el pivot para dividir la tarea de ordenamiento
	int pivot = arreglo[(izquierda + derecha) / 2];

	cout << "Pivot -->" << pivot << endl;

	//mientras el valor actual de l�mite izquierdo sea menor o igual al l�mite derecho
	while (i <= j) {
		//mientras el valor en la posici�n i sea menor que el pivot que encontramos antes
		while (arreglo[i] < pivot) {
			i++;//incrementamos el l�mite izquierdo
		}
		//mientras el valor en la posici�n j sea mayor que el pivot que encontramos antes
		while (arreglo[j] > pivot) {
			j--;//decrementamos el valor de j
		}
		//f�jense como los l�mites empiezan a acercarse entre s� luego de los while anteriores.

		//si se sigue cumpliendo la condici�n inicial
		if (i <= j) {
			//momento de realizar los intercambios
			temporal = arreglo[i];
			arreglo[i] = arreglo[j];
			arreglo[j] = temporal;
			//nuevamente se acercan los l�mites
			i++;
			j--;
		}
	}

	//Cuando ya i y j han excedido sus l�mites realizamos comparaciones

	if (izquierda < j) {
		/*
			La funci�n se llama as� misma pero en esta ocasi�n, ya no trabaja sobre todo el arreglo.
			En este caso, se pasa el arreglo que se recibi�, el l�mite izquierdo y como l�mite derecho 
			el valor obtenido en J. Se llamar� as� mismo, buscar� su pivot nuevamente, etc.
		*/
		Quicksort(arreglo, izquierda, j);
	}
	if (i < derecha) {
		/*
			An�logamente al IF anterior pero mirando el otro lado del arreglo
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
		1.- Necesito trabajar este algoritmo aplicando recursividad (se llama a s� mismo), por eso lo hago en una funci�n.
		Sus par�metros son el vector a manipular, la posici�n inicial y la posici�n final de nuestros elementos
	*/
	Quicksort(valores, 0, 4);

	cout << "Valores ordenados:" << endl;
	for (int i = 0; i < 5; i++) {
		cout << valores[i] << endl;
	}

	getchar();
	return 0;
}
#include <iostream>

using namespace std;

int main() {
	int valores[] = { 34, 6, 9, 13, 45, 1, -8, -1, 5, 0 };
	//es necesario conocer el mínimo valor actual. También necesito trabajar con auxiliares
	int minimo, auxiliar;

	cout << "Valores desordenados: " << endl;
	for (int i = 0; i < 10; i++) {
		cout << valores[i] << endl;
	}

	//Nuevamente necesito recorrer todos los elementos...
	for (int i = 0; i < 10; i++) {
		//de arranque en cada iteración suponemos que el menor es la posición actual
		minimo = i;
		//recorro los elementos del vector pero a partir del siguiente (en este caso no empiezo en 0)
		for (int j = i + 1; j < 10; j++) {
			//si el valor a la derecha de i es menor al mínimo entonces encontramos un nuevo mínimo
			if (valores[j] < valores[minimo]) {
				minimo = j;//y como lo encontramos lo asignamos.
			}
		}
		//salvamos el valor del elemento inicial o actual en una variable auxiliar
		auxiliar = valores[i];
		//en esa posición actual almacenamos el contenido de la posición donde se encontró el mínimo
		valores[i] = valores[minimo];
		//y donde está el mínimo almacenamos el auxiliar...
		valores[minimo] = auxiliar;
		//... nuevamente, la cuestión es el intercambio y como lo hacemos.
	}

	cout << "Valores ordenados: " << endl;
	for (int i = 0; i < 10; i++) {
		cout << valores[i] << endl;
	}

	getchar();
	return 0;
}
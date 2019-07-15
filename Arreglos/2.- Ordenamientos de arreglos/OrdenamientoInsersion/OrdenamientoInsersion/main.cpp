#include <iostream>

using namespace std;

int main() {

	int valores[] = { 4, 9, 12, 56, 43, 12, 78, 100, -5, 4 };
	int auxiliar;
	int index;

	cout << "Valores desordenados:" << endl;
	for (int i = 0; i < 10; i++) {
		cout << valores[i] << endl;
	}

	/*	En este caso necesito trabajar con un índice...
	
	*/
	for (int i = 0; i < 10; i++) {//recorro todos los elementos del vector
		//el indice lo posiciono en 0 inicialmente... luego en 1 y así sucesivamente vaya iterando FOR.
		index = i;
		//almaceno auxiliarmente el valor actual del arreglo, ese valor irá a la posición que corresponde según el indice actual.
		auxiliar = valores[i];
		//si el indice es mayor que 0 y la posición anterior del índice es mayor que el auxiliar genero el intercambio
		while (index > 0 && valores[index - 1] > auxiliar) {
			//el valor según el índice es igual al valor anterior (mas a la derecha del vector).
			valores[index] = valores[index - 1];
			//retrocedo el índice y esta acción se va a llevar adelante hasta que no se cumpla la condición
			index--;
		}
		//estalece el valor para la posición actual del vector según lo salvado con el auxiliar
		valores[index] = auxiliar;
	}

	cout << "Valores ordenados:" << endl;
	for (int i = 0; i < 10; i++) {
		cout << valores[i] << endl;
	}

	getchar();
	return 0;
}
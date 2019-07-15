#include <iostream>

using namespace std;

int main() {
	int auxiliar;
	int valores[] = { 40, 19, 200, 31, 53, 1000, 15, 1, 0, -15 };

	cout << "Valores desordenados: " << endl;
	for (int i = 0; i < 10; i++) {
		cout << valores[i] << endl;
	}
	
	/*	Necesito un doble FOR para recorrer y manipular el vector. La diferencia es que en el primero
		nuestro límite es 10 (por la cantidad de elementos) y en el segundo el límite es 9 (para no salirnos del vector)
	*/
	for (int i = 0; i < 10; i++) {//lo necesito para recorrerlos todos
		for (int j = 0; j < 9; j++) {//lo necesito para observar el siguiente
			if (valores[j] > valores[j + 1]) {//Si el valor actual es mayor que el valor siguiente
				//lo que tengo en el valor actual lo recuerdo en la variable auxiliar
				auxiliar = valores[j];
				//lo que tengo en la posición siguiente lo coloco en la posición de lectura actual
				valores[j] = valores[j + 1];
				//y lo que tenía en la posición actual (que sobreescribí antes) lo tenía salvado en el auxiliar
				//y de ese modo provoco un intercambio
				valores[j + 1] = auxiliar;
			}
		}
	}
	
	cout << "Valores ordenados: " << endl;
	for (int i = 0; i < 10; i++) {
		cout << valores[i] << endl;
	}

	getchar();
	return 0;
}
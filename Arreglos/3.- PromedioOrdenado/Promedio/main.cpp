#include "Scene.h"

int main() {
	srand(time(0));//planto semilla para obtener valores aleatorios distintos
	bool continuo = true;
	while (continuo) {
		//creo una escena pasando los datos para la ventana en el constructor y
		//le doy tooooodo el control de la aplicación a la escena de juego 
		Scene s = Scene(142 * 6, 350, "Promedio de Puntajes");
		continuo = s.isReset();//bueno... no todo el control xD
	}
	return 0;
}
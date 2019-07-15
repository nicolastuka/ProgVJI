#include "Scene.h"

Scene::Scene(int width, int height, string title) {
	window = new RenderWindow(VideoMode(width, height), title);
	//window->setFramerateLimit(60);  ****esto está de gusto porque no hay animaciones****
	evt = new Event();

	LoadVectorEntities();//1.- Vamos a cargar los vectores...

	int promedio = 0;
	for (int i = 0; i < 6; i++) {
		promedio += e[i]->GetValue();
	}
	promedio /= 6;

	font = new Font();
	font->loadFromFile("assets/arial.ttf");

	textPromedio = new Text();
	textPromedio->setFont(*font);
	textPromedio->setFillColor(Color::White);
	textPromedio->setCharacterSize(72);
	textPromedio->setPosition(0, 50);

	textPromedio->setString(GetPromedioString(promedio));

	textMethodSelected = new Text();
	textMethodSelected->setFont(*font);
	textMethodSelected->setFillColor(Color::Green);
	textMethodSelected->setCharacterSize(20);
	textMethodSelected->setPosition(width * .5f, 150);
	textMethodSelected->setString("");
	
	textInstructions = new Text();
	textInstructions->setFont(*font);
	textInstructions->setFillColor(Color::Cyan);
	textInstructions->setCharacterSize(24);
	textInstructions->setPosition(width * .66f, 0);
	textInstructions->setString("[B] Ordena por burbuja\n[I] Ordena por inserción\n[S] Ordena por selección\n[Q] Ordena por Quicksort");

	Update();//2.- Como a mi me gusta... llamo al loop de juego desde el constructor
}

Scene::~Scene() {
	delete window;
}

void Scene::Update() {
	while (window->isOpen())
	{
		ProcessEvents();//3.- Este método contiene la lectura de teclas y ejecuta los métodos de ordenamiento
		window->clear();
		for (int i = 0; i < 6; i++) {
			e[i]->Draw(window);//4.- Para no utilizar tantos getters de elementos de la clase Entity directamente le
								//envío la dirección de memoria de la ventana que estoy usando para que la clase
								//entity la manipule
		}
		window->draw(*textMethodSelected);
		window->draw(*textPromedio);
		window->draw(*textInstructions);
		window->display();
		if (reset) {
			return;
		}
	}
}

void Scene::ProcessEvents() {
	while (window->pollEvent(*evt)) {
		if (evt->type == Event::Closed) {
			reset = false;
			window->close();
		}
		if (Keyboard::isKeyPressed(Keyboard::B)) {
			OrderByBubble();//5.- Llamo a este método por ejemplo que es el de burbuja... si presioné B (se explica en 9)
			textMethodSelected->setString("Método seleccionado Burbuja");
		}
		if (Keyboard::isKeyPressed(Keyboard::I)) {
			OrderByInsertion();//6.- Allí se explica (se explica en 11)
			textMethodSelected->setString("Método seleccionado Inserción");
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			OrderBySelection();//7.- Allí se explica (se explica en 12)
			textMethodSelected->setString("Método seleccionado Selección");
		}
		if (Keyboard::isKeyPressed(Keyboard::Q)) {
			OrderByQuicksort(valuesEntities, 0, 6);//8.- Allí se explica (se explica en 13)
			//como el método es iterativo no puedo incluir por su lógica el ordenamiento
			//gráfico de los elementos dentro del método.
			for (int i = 0; i < 6; i++) {
				e[i]->SetPosition(i);
			}
			textMethodSelected->setString("Método seleccionado Quicksort");
		}
		if (Keyboard::isKeyPressed(Keyboard::R)) {
			reset = true;
		}
	}
}

void Scene::LoadVectorEntities() {
	for (int i = 0; i < 6; i++) {//un ciclo para crear las entidades
		e[i] = new Entity(i);//a cada entidad que se almacena en el vector le paso como parametro el valor del iterador
		//cuando se crea una entidad, la misma obtiene el valor aleatorio. Ese valor lo
		//asigno al otro vector que utilicé (el de enteros)
		valuesEntities[i] = e[i]->GetValue();
	}
}

string Scene::GetPromedioString(int promedio) {
	stringstream ss;
	ss << "Promedio: " << promedio;
	return ss.str();
}

/*9.- 
	MÉTODO BURBUJA
	Aquí la cuestión es que realicemos el recorrido del vector una y otra vez por eso les diría que no es el más
	optimo...
	Tenemos que dar seis vueltitas porque son todos los elementos que tenemos
	Luego viene el for que nos interesa...
	pero fíjense que vamos de 0 a 5 porque cuando quiera comparar el actual con el siguiente en el IF
	nos vamos a terminar saliendo del vector (quedaría en la posición que no tenemos nada)
*/

/*void Scene::OrderByBubble() {
	int aux;
	for(int i=0; i < 6; i++) {
		for (int j = 0; j < 5; j++) {
			if (valuesEntities[j] > valuesEntities[j + 1]) {
				Entity *auxE = e[j];
				e[j] = e[j + 1];
				e[j + 1] = auxE;
				aux = valuesEntities[j];
				valuesEntities[j] = valuesEntities[j + 1];
				valuesEntities[j + 1] = aux;
			}
		}
	}
	for (int i = 0; i < 6; i++) {//aquí se reordena gráficamente...
		e[i]->SetPosition(i);
	}
}*/

/*

10.- Recuerdan que les dije que era algo de gusto utilizar los dos vectores?
Bueno... fíjense que trabajo los valores enteros según lo que tengo almacenado en la propia entidad
Lo ideal sería que realicen el ordenamiento según el siguiente ejemplo:

*/


void Scene::OrderByBubble() {
	for (int i = 0; i < 6; i++) {//recuerden que esto lo hago para realizar tantas comparaciones como elementos tenga (no muy óptimo)
		for (int j = 0; j < 5; j++) {
			//si el valor contenido en la posición actual es mayor al de la posición siguiente realizo el intercambio
			if (e[j]->GetValue() > e[j + 1]->GetValue()) {
				//si se cumple la condición provoco el intercambio
				Entity *auxE = e[j];
				e[j] = e[j + 1];
				e[j + 1] = auxE;
			}
		}
	}
	for (int i = 0; i < 6; i++) {//aquí se reordena gráficamente...
		e[i]->SetPosition(i);
	}
}

/*

11.- MÉTODO POR INSERCIÓN 

	En este caso, debemos manipular un índice para reconocer nuestra posición actual y mirar el valor contenido a 
	la izquierda para determinar si es correcto realizar el intercambio...

*/
void Scene::OrderByInsertion() {
	int auxiliar;
	int index;
	for (int i = 0; i < 6; i++) {//iteramos sobre todos los elementos del vector
		index = i;//el indice es el valor actual de i
		auxiliar = valuesEntities[i];//almaceno en el auxiliar (por las dudas) el valor que hay en esa posición
		Entity *auxE = e[index];//la misma historia con el auxiliar de la entidad
		//y aquí vemos esta verificación... primero observamos no apuntar con el índice al primer elemento y luego
		//ver si la posición anterior es mayor al auxiliar
		//aclaro, el índice tiene que ser mayor al primer elemento porque no hay elementos más a la izquierda
		while (index > 0 && valuesEntities[index - 1] > auxiliar) {
			//si se cumple la condición ahí va el intercambio
			e[index] = e[index - 1];
			valuesEntities[index] = valuesEntities[index - 1];
			index--;//el índice se reduce...
		}
		//cuando finaliza el while es porque se determinó donde está el elemento a intercambiar
		//la lectura sería...
		//si el indice es cero dejo todo como está
		//si el indice es 1 me fijo como va a la izquierda... si se cumple la condición el índice vuelve a cero luego de realizar las asignaciones pertinentes
		//como el indice vuelve a ser cero, sale del while por ende, almacena los auxiliares en la nueva posición del índice
		//y así hasta que llega al último elemento.
		e[index] = auxE;
		valuesEntities[index] = auxiliar;
	}
	for (int i = 0; i < 6; i++) {//ordenamietno gráfico
		e[i]->SetPosition(i);
	}
}

/*

12.- MÉTODO POR SELECCIÓN 

	En este, debemos realizar un recorrido e ir buscando el valor mínimo de todo el arreglo para realizar comparaciones
	Inicialmente decimos que el valor mínimo es el valor de i (como para decir algo porque luego en el siguiente FOR
	determinamos cual es realmente la posición donde se encuentra el valor mínimo)

*/

void Scene::OrderBySelection() {
	int minimo, auxiliar;
	for (int i = 0; i < 6; i++) {
		minimo = i;
		for (int j = i + 1; j < 6; j++) {
			//Si el valor siguiente en el vector es menor que el valor en la posición mínimo(i)
			//determino que el mínimo se encuentra en la posición siguiente
			if (valuesEntities[j] < valuesEntities[minimo]) {
				minimo = j;//este es mi verdadero mínimo... o quizás más adelante el mínimo pueda llegar a ser otro elemento
			}
		}
		//una vez que se logra determinar cual es el mínimo se realiza el intercambio de valores
		auxiliar = valuesEntities[i];
		Entity *auxE = e[i];
		valuesEntities[i] = valuesEntities[minimo];
		e[i] = e[minimo];
		valuesEntities[minimo] = auxiliar;
		e[minimo] = auxE;
	}
	for (int i = 0; i < 6; i++) {//grafico con la nueva posición
		e[i]->SetPosition(i);
	}
}

/*

13.- MÉTODO QUICKSORT

	Este es el mejor método que podemos utilizar si tenemos una amplia cantidad de elementos en un vector
	También es el método de ordenamiento más complicado de comprender (o por lo menos esa es mi opinión)
	Aquí la regla es dividir el arreglo, fíjense que el arreglo se pasa como parámetro, junto con un entero que indica
	el extremo izquierdo y otro que indica el último elemento del vector (lo ven cuando lo mando a llamar en ProcessEvents

*/

void Scene::OrderByQuicksort(int *arreglo, int izquierda, int derecha) {
	//para simplificar y también para no perder la referencia de los extremos iniciales realizo las siguientes
	//asignaciones en i y en j
	int i = izquierda;
	int j = derecha;
	int temporal;
	//establecemos el pivot (el centro del arreglo)
	int pivot = arreglo[(izquierda + derecha) / 2];

	//si el extremo izquierdo es menor o igual al extremo derecho vamos a realizar intercambios entre ambos lados
	//del arreglo o vector en este caso
	while (i <= j) {
		//estos dos while son porque si recuerdan, si ambos fueran índices, debemos ver como estos se acercan hasta el pivot
		//o sea el que está a la izquuierda avanza hacia la derecha...
		while (arreglo[i] < pivot) {
			i++;
		}
		//y el que está a la derecha avanza hacia la izquierda
		while (arreglo[j] > pivot) {
			j--;
		}
		//una vez acercados lo más posible estos índices realizamos la operación de intercambio...
		if (i <= j) {
			Entity *auxE = e[i];
			temporal = arreglo[i];
			e[i] = e[j];
			arreglo[i] = arreglo[j];
			e[j] = auxE;
			arreglo[j] = temporal;
			i++;
			j--;
		}
	}
	//cuando ya el valor de i sea mayor que el de j (porque i avanzó en posiciones más a la derecha que j)
	//Aquí se observa la recursividad del método:
	//ahora... va a llamarse así mismo si el valor de izquierda es menor que el valor resultante de J pero...
	//fíjense con cuidad que izquierda jamás alteró su valor...
	if (izquierda < j) {
		//En este caso cumplida la condición, se vuelve a enviar el arreglo pero cambia el extremo de la derecha
		//que es el valor resultante de J de todo el bucle que se trabajó más arriba en este método
		OrderByQuicksort(arreglo, izquierda, j);//aquí se está llamando así mismo
	}
	//y ahora pasa la misma situación, la derecha jamás se tocó pero se compara contra i
	if (i < derecha) {
		//En este caso cumplida la condición, se vuelve a enviar el arreglo pero cambia el extremo de la izquierda
		//que es el valor resultante de I de todo el bucle que se trabajó más arriba en este método
		OrderByQuicksort(arreglo, i, derecha);
	}
	//ATENCIÓN:
	//no necesariamente se llama al método dos veces, a veces se cumplen las dos condiciones, en otras una y cuando
	//ya no se cumple ninguna finaliza la ejecución del algoritmo.
}

bool Scene::isReset() {
	return reset;
}
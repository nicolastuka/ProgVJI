#include "Scene.h"

Scene::Scene(int width, int height, string title) {
	window = new RenderWindow(VideoMode(width, height), title);
	//window->setFramerateLimit(60);  ****esto est� de gusto porque no hay animaciones****
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
	textInstructions->setString("[B] Ordena por burbuja\n[I] Ordena por inserci�n\n[S] Ordena por selecci�n\n[Q] Ordena por Quicksort");

	Update();//2.- Como a mi me gusta... llamo al loop de juego desde el constructor
}

Scene::~Scene() {
	delete window;
}

void Scene::Update() {
	while (window->isOpen())
	{
		ProcessEvents();//3.- Este m�todo contiene la lectura de teclas y ejecuta los m�todos de ordenamiento
		window->clear();
		for (int i = 0; i < 6; i++) {
			e[i]->Draw(window);//4.- Para no utilizar tantos getters de elementos de la clase Entity directamente le
								//env�o la direcci�n de memoria de la ventana que estoy usando para que la clase
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
			OrderByBubble();//5.- Llamo a este m�todo por ejemplo que es el de burbuja... si presion� B (se explica en 9)
			textMethodSelected->setString("M�todo seleccionado Burbuja");
		}
		if (Keyboard::isKeyPressed(Keyboard::I)) {
			OrderByInsertion();//6.- All� se explica (se explica en 11)
			textMethodSelected->setString("M�todo seleccionado Inserci�n");
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			OrderBySelection();//7.- All� se explica (se explica en 12)
			textMethodSelected->setString("M�todo seleccionado Selecci�n");
		}
		if (Keyboard::isKeyPressed(Keyboard::Q)) {
			OrderByQuicksort(valuesEntities, 0, 6);//8.- All� se explica (se explica en 13)
			//como el m�todo es iterativo no puedo incluir por su l�gica el ordenamiento
			//gr�fico de los elementos dentro del m�todo.
			for (int i = 0; i < 6; i++) {
				e[i]->SetPosition(i);
			}
			textMethodSelected->setString("M�todo seleccionado Quicksort");
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
		//asigno al otro vector que utilic� (el de enteros)
		valuesEntities[i] = e[i]->GetValue();
	}
}

string Scene::GetPromedioString(int promedio) {
	stringstream ss;
	ss << "Promedio: " << promedio;
	return ss.str();
}

/*9.- 
	M�TODO BURBUJA
	Aqu� la cuesti�n es que realicemos el recorrido del vector una y otra vez por eso les dir�a que no es el m�s
	optimo...
	Tenemos que dar seis vueltitas porque son todos los elementos que tenemos
	Luego viene el for que nos interesa...
	pero f�jense que vamos de 0 a 5 porque cuando quiera comparar el actual con el siguiente en el IF
	nos vamos a terminar saliendo del vector (quedar�a en la posici�n que no tenemos nada)
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
	for (int i = 0; i < 6; i++) {//aqu� se reordena gr�ficamente...
		e[i]->SetPosition(i);
	}
}*/

/*

10.- Recuerdan que les dije que era algo de gusto utilizar los dos vectores?
Bueno... f�jense que trabajo los valores enteros seg�n lo que tengo almacenado en la propia entidad
Lo ideal ser�a que realicen el ordenamiento seg�n el siguiente ejemplo:

*/


void Scene::OrderByBubble() {
	for (int i = 0; i < 6; i++) {//recuerden que esto lo hago para realizar tantas comparaciones como elementos tenga (no muy �ptimo)
		for (int j = 0; j < 5; j++) {
			//si el valor contenido en la posici�n actual es mayor al de la posici�n siguiente realizo el intercambio
			if (e[j]->GetValue() > e[j + 1]->GetValue()) {
				//si se cumple la condici�n provoco el intercambio
				Entity *auxE = e[j];
				e[j] = e[j + 1];
				e[j + 1] = auxE;
			}
		}
	}
	for (int i = 0; i < 6; i++) {//aqu� se reordena gr�ficamente...
		e[i]->SetPosition(i);
	}
}

/*

11.- M�TODO POR INSERCI�N 

	En este caso, debemos manipular un �ndice para reconocer nuestra posici�n actual y mirar el valor contenido a 
	la izquierda para determinar si es correcto realizar el intercambio...

*/
void Scene::OrderByInsertion() {
	int auxiliar;
	int index;
	for (int i = 0; i < 6; i++) {//iteramos sobre todos los elementos del vector
		index = i;//el indice es el valor actual de i
		auxiliar = valuesEntities[i];//almaceno en el auxiliar (por las dudas) el valor que hay en esa posici�n
		Entity *auxE = e[index];//la misma historia con el auxiliar de la entidad
		//y aqu� vemos esta verificaci�n... primero observamos no apuntar con el �ndice al primer elemento y luego
		//ver si la posici�n anterior es mayor al auxiliar
		//aclaro, el �ndice tiene que ser mayor al primer elemento porque no hay elementos m�s a la izquierda
		while (index > 0 && valuesEntities[index - 1] > auxiliar) {
			//si se cumple la condici�n ah� va el intercambio
			e[index] = e[index - 1];
			valuesEntities[index] = valuesEntities[index - 1];
			index--;//el �ndice se reduce...
		}
		//cuando finaliza el while es porque se determin� donde est� el elemento a intercambiar
		//la lectura ser�a...
		//si el indice es cero dejo todo como est�
		//si el indice es 1 me fijo como va a la izquierda... si se cumple la condici�n el �ndice vuelve a cero luego de realizar las asignaciones pertinentes
		//como el indice vuelve a ser cero, sale del while por ende, almacena los auxiliares en la nueva posici�n del �ndice
		//y as� hasta que llega al �ltimo elemento.
		e[index] = auxE;
		valuesEntities[index] = auxiliar;
	}
	for (int i = 0; i < 6; i++) {//ordenamietno gr�fico
		e[i]->SetPosition(i);
	}
}

/*

12.- M�TODO POR SELECCI�N 

	En este, debemos realizar un recorrido e ir buscando el valor m�nimo de todo el arreglo para realizar comparaciones
	Inicialmente decimos que el valor m�nimo es el valor de i (como para decir algo porque luego en el siguiente FOR
	determinamos cual es realmente la posici�n donde se encuentra el valor m�nimo)

*/

void Scene::OrderBySelection() {
	int minimo, auxiliar;
	for (int i = 0; i < 6; i++) {
		minimo = i;
		for (int j = i + 1; j < 6; j++) {
			//Si el valor siguiente en el vector es menor que el valor en la posici�n m�nimo(i)
			//determino que el m�nimo se encuentra en la posici�n siguiente
			if (valuesEntities[j] < valuesEntities[minimo]) {
				minimo = j;//este es mi verdadero m�nimo... o quiz�s m�s adelante el m�nimo pueda llegar a ser otro elemento
			}
		}
		//una vez que se logra determinar cual es el m�nimo se realiza el intercambio de valores
		auxiliar = valuesEntities[i];
		Entity *auxE = e[i];
		valuesEntities[i] = valuesEntities[minimo];
		e[i] = e[minimo];
		valuesEntities[minimo] = auxiliar;
		e[minimo] = auxE;
	}
	for (int i = 0; i < 6; i++) {//grafico con la nueva posici�n
		e[i]->SetPosition(i);
	}
}

/*

13.- M�TODO QUICKSORT

	Este es el mejor m�todo que podemos utilizar si tenemos una amplia cantidad de elementos en un vector
	Tambi�n es el m�todo de ordenamiento m�s complicado de comprender (o por lo menos esa es mi opini�n)
	Aqu� la regla es dividir el arreglo, f�jense que el arreglo se pasa como par�metro, junto con un entero que indica
	el extremo izquierdo y otro que indica el �ltimo elemento del vector (lo ven cuando lo mando a llamar en ProcessEvents

*/

void Scene::OrderByQuicksort(int *arreglo, int izquierda, int derecha) {
	//para simplificar y tambi�n para no perder la referencia de los extremos iniciales realizo las siguientes
	//asignaciones en i y en j
	int i = izquierda;
	int j = derecha;
	int temporal;
	//establecemos el pivot (el centro del arreglo)
	int pivot = arreglo[(izquierda + derecha) / 2];

	//si el extremo izquierdo es menor o igual al extremo derecho vamos a realizar intercambios entre ambos lados
	//del arreglo o vector en este caso
	while (i <= j) {
		//estos dos while son porque si recuerdan, si ambos fueran �ndices, debemos ver como estos se acercan hasta el pivot
		//o sea el que est� a la izquuierda avanza hacia la derecha...
		while (arreglo[i] < pivot) {
			i++;
		}
		//y el que est� a la derecha avanza hacia la izquierda
		while (arreglo[j] > pivot) {
			j--;
		}
		//una vez acercados lo m�s posible estos �ndices realizamos la operaci�n de intercambio...
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
	//cuando ya el valor de i sea mayor que el de j (porque i avanz� en posiciones m�s a la derecha que j)
	//Aqu� se observa la recursividad del m�todo:
	//ahora... va a llamarse as� mismo si el valor de izquierda es menor que el valor resultante de J pero...
	//f�jense con cuidad que izquierda jam�s alter� su valor...
	if (izquierda < j) {
		//En este caso cumplida la condici�n, se vuelve a enviar el arreglo pero cambia el extremo de la derecha
		//que es el valor resultante de J de todo el bucle que se trabaj� m�s arriba en este m�todo
		OrderByQuicksort(arreglo, izquierda, j);//aqu� se est� llamando as� mismo
	}
	//y ahora pasa la misma situaci�n, la derecha jam�s se toc� pero se compara contra i
	if (i < derecha) {
		//En este caso cumplida la condici�n, se vuelve a enviar el arreglo pero cambia el extremo de la izquierda
		//que es el valor resultante de I de todo el bucle que se trabaj� m�s arriba en este m�todo
		OrderByQuicksort(arreglo, i, derecha);
	}
	//ATENCI�N:
	//no necesariamente se llama al m�todo dos veces, a veces se cumplen las dos condiciones, en otras una y cuando
	//ya no se cumple ninguna finaliza la ejecuci�n del algoritmo.
}

bool Scene::isReset() {
	return reset;
}
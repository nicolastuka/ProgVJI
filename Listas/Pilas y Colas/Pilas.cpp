#include <iostream>
using namespace std;

//m�s f�cil una estructura que una clase para este ejemplo sencillo
struct Nodo {
	char letra;//la letra que es lo que almancena
	Nodo *siguienteNodo;//apuntador al siguiente nodo
};

/*

Aqu� insertamos un nodo con un valor y ese nodo va a apuntar al resto de la pila

Paso por referencia (&) la pila para poder modificarla, y tambi�n el valor a 
almacenar.

NOTA: pasar la pila sin referencia sirve a efectos de realizar su lectura pero
no para modificarla que es lo que nos interesa en esta estructura.

*/
void PushNodo(Nodo *&pila, char letraInsertar)
{
	Nodo *nueva_letra = new Nodo();//creamos un nuevo nodo en memoria
	nueva_letra->letra = letraInsertar;//a ese nodo le damos un valor
	nueva_letra->siguienteNodo = pila;//le indicamos que el siguiente es el total de la pila
	pila = nueva_letra;//y AQU� estoy MODIFICANDO la pila
}

/*

Aqu� quitamos el elemento de la pila (el primero de arriba) y lo sacamos de la
estructura de datos.

Paso nuevamente por referencia la estructura para poder modificarla y una reserva
de memoria (variable) creada en otro lugar para almacenar un valor de tipo char.

Que pasa, la operaci�n desvincula el elemento de la pila por ende para poder utilizar
ese elemento quitado necesito resguardarlo en alg�n lado, por eso paso la referencia
a la variable creada en la funci�n main. Del mismo modo que la pila, podemos variar
su valor desde la funci�n.

*/

void PopNodo(Nodo *&pila, char &letraAObtener)
{
	Nodo *aux = pila;//accedo al primer elemento de la pila
	letraAObtener = aux->letra;//obtengo su valor Y LO SALVO
	pila = aux->siguienteNodo;//MODIFICO la pila indicando que el tope ahora es la siguiente a la primera
	delete aux;//dejo de reservar la memoria para ese elemento quitado
}

int main(int argc, char *argv[]) {
	Nodo *pila = NULL;//aqu� podemos pensar que estamos creando una Pila de Nodos
	char valueObtenidoPorPop;//para contener la letra que quite de la estructura
	//Agrego tres elementos, primero la U, luego la N y finalmente la L
	PushNodo(pila, 'U');//le el puntero a la pila y el valor que voy a agregar
	PushNodo(pila, 'N');
	PushNodo(pila, 'L');
	while(pila != NULL)
	{
		//le paso la pila y la variable donde quiero contener la letra para mostrarla luego
		PopNodo(pila, valueObtenidoPorPop);
		cout<<valueObtenidoPorPop<<endl;//ahora muestro el valor
	}
	/*
	Repito la iteraci�n pero no va a mostrar nada porque la pila se vaci� en la 
	iteraci�n anterior, recuerden que por cada Pop voy "olvidando" el lugar de la 
	memoria	reservado, se podr�an haber preguntado entonces para realic� un delete:
	para que el sistema disponga de esa posici�n de memoria.
	*/
	while(pila != NULL)
	{
		PopNodo(pila, valueObtenidoPorPop);
		cout<<valueObtenidoPorPop<<endl;
	}
	return 0;
}


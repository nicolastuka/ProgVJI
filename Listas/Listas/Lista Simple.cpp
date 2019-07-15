#include <iostream>
using namespace std;

//Lista enlazada simple o abierta orientada a objetos
//Ejemplo redactado en base a la lectura de la Unidad 2

// Clase Nodo
class Nodo {
private:
	int valorDelNodo;
	Nodo *siguienteNodo;
	friend class Lista;
public:
	Nodo(int valorParaAlmacenar, Nodo *siguiente = NULL)
	{
		valorDelNodo = valorParaAlmacenar;
		siguienteNodo = siguiente;
	}
};

typedef Nodo *pNodo;

//clase lista
class Lista {
private:
	pNodo primerNodo;
	pNodo actualNodo;
public:
	Lista()
	{
		primerNodo = actualNodo = NULL;
	}
	
	void Siguiente()
	{
		if (actualNodo)
		{
			actualNodo = actualNodo->siguienteNodo;
		}
	}
	
	int CantidadElementos()
	{
		if (ListaVacia())
		{
			return 0;
		}
		int retorno = 0;
		actualNodo = primerNodo;
		while (actualNodo != NULL)
		{
			Siguiente();
			retorno++;
		}
		return retorno;
	}
	
	int Primero()
	{
		actualNodo = primerNodo;
		return primerNodo->valorDelNodo;
	}
	
	int Ultimo()
	{
		actualNodo = primerNodo;
		if (!ListaVacia())
		{
			while(actualNodo->siguienteNodo)
			{
				Siguiente();
			}
		}
		return actualNodo->valorDelNodo;
	}
	
	string RecorrerLista()
	{
		string retorno = "";
		actualNodo = primerNodo;
		if (!ListaVacia())
		{
			retorno = std::to_string(actualNodo->valorDelNodo);
			while(actualNodo->siguienteNodo)
			{
				Siguiente();
				retorno += " - " + to_string(actualNodo->valorDelNodo);
			}
		}
		return retorno;
	}
	
	bool ListaVacia()
	{
		if (primerNodo == NULL)
		{
			return true;
		}
		return false;
	}
	
	void Insertar(int valorParaAlmacenarEnNodo)
	{
		pNodo anteriorNodo;
		
		if (ListaVacia() || primerNodo->valorDelNodo > valorParaAlmacenarEnNodo)
		{
			primerNodo = new Nodo(valorParaAlmacenarEnNodo, primerNodo);
		}
		else
		{
				anteriorNodo = primerNodo;
				while(anteriorNodo->siguienteNodo && anteriorNodo->siguienteNodo->valorDelNodo <= valorParaAlmacenarEnNodo)
				{
					anteriorNodo = anteriorNodo->siguienteNodo;
				}
				anteriorNodo->siguienteNodo = new Nodo(valorParaAlmacenarEnNodo, anteriorNodo->siguienteNodo);
		}
	}
	
	void Eliminar(int valorDeLaListaAEliminar)
	{
		pNodo anteriorNodo, nodo;
		nodo = primerNodo;
		anteriorNodo = NULL;
		while(nodo && nodo->valorDelNodo < valorDeLaListaAEliminar)
		{
			anteriorNodo = nodo;
			nodo = nodo->siguienteNodo;
		}
		if(!nodo || nodo->valorDelNodo != valorDeLaListaAEliminar)
		{
			return;
		}
		else
		{
			if (!anteriorNodo)
			{
				primerNodo = nodo->siguienteNodo;
			}
			else
			{
				anteriorNodo->siguienteNodo = nodo->siguienteNodo;
			}
			delete nodo;
		}
	}
};

int main(int argc, char *argv[]) {
	Lista l;
	cout<<"La lista esta vacia? "<<((l.ListaVacia()) ? "Si" : "No")<<endl;
	l.Insertar(10);
	
	cout<<"La lista esta vacia? "<<((l.ListaVacia()) ? "Si" : "No")<<endl;
	
	cout<<"Actualmente el Primer valor de la lista es: "<<l.Primero()<<endl;
	
	l.Insertar(11);
	l.Insertar(9);
	l.Insertar(8);
	l.Insertar(1);
	l.Insertar(13);
	
	cout<<"Luego de añadir 5 nodos:"<<endl;
	
	cout<<"El Primer valor de la lista es: "<<l.Primero()<<endl;
	
	cout<<"El Ultimo valor de la lista es: "<<l.Ultimo()<<endl;
	
	cout<<"Voy a recorrer todos los elementos de la lista y mostrarlos: "<<l.RecorrerLista()<<endl;
	
	cout<<endl<<"Fíjense que actualmente tengo "<<l.CantidadElementos()<<" elementos"<<endl;
	
	cout<<"Voy a proceder a eliminar el elemento con valor 10 de la lista y luego\nvolver a imprimir la lista completa: ";
	l.Eliminar(10);
	cout<<l.RecorrerLista();
	
	cout<<endl<<"Fíjense que ahora tengo "<<l.CantidadElementos()<<" elementos";
	return 0;
}


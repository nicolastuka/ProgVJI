#include <iostream>
using namespace std;

struct Nodo 
{
	int dato;
	Nodo *izquierda;
	Nodo *derecha;
	Nodo *padre;
};

Nodo* CrearNodo(int valor, Nodo *padre)
{
	Nodo *nodo = new Nodo();
	nodo->dato = valor;
	nodo->derecha = NULL;
	nodo->izquierda = NULL;
	nodo->padre = padre;
	return nodo;
}

void MostrarArbol(Nodo *arbol, int contador)
{
	if (arbol == NULL)
	{
		//cout<<"\t\t\t\tHoja del árbol"<<endl<<endl;
		return;
	}
	else
	{
		MostrarArbol(arbol->derecha, contador + 1);
		for(int i = 0; i < contador; i++)
		{
			cout<<"\t";
		}
		cout<<arbol->dato<<endl;
		MostrarArbol(arbol->izquierda, contador + 1);
	}
}

bool BuscarNodo(Nodo *arbol, int n)
{
	if (arbol == NULL)
	{
		return false;
	}
	else if (arbol->dato == n)
	{
		return true;
	}
	else if (n < arbol->dato)
	{
		BuscarNodo(arbol->izquierda, n);
	}
	else
	{
		BuscarNodo(arbol->derecha, n);
	}
}

Nodo *Minimo(Nodo *arbol)
{
	if (arbol == NULL)
	{
		return NULL;
	}
	if (arbol->izquierda)
	{
		return Minimo(arbol->izquierda);
	}
	//else
	//{
		return arbol;
	//}
}

void Reemplazar(Nodo *arbol, Nodo *nuevo)
{
	if (arbol->padre)
	{
		if (arbol->dato == arbol->padre->izquierda->dato)
		{
			arbol->padre->izquierda = nuevo;
		}
		else if (arbol->dato == arbol->padre->derecha->dato)
		{
			arbol->padre->derecha = nuevo;
		}
	}
	if (nuevo)
	{
		nuevo->padre = arbol->padre;
	}
}

void DestruirNodo(Nodo *nodo)
{
	nodo->izquierda = NULL;
	nodo->derecha = NULL;
	delete nodo;
}

void InsertarNodoArbol(Nodo *&arbol, Nodo *padre, int n)
{
	if (arbol == NULL)
	{
		Nodo *nodo = CrearNodo(n, padre);
		arbol = nodo;
	}
	else
	{
		int valorRaiz = arbol->dato;
		if (n < valorRaiz)
		{
			InsertarNodoArbol(arbol->izquierda, arbol, n);
		}
		else
		{
			InsertarNodoArbol(arbol->derecha, arbol, n);
		}
	}
}

void EliminarNodoEncontrado(Nodo *nodoEliminar)
{
	//si es nodo hoja
	if (nodoEliminar->derecha == NULL && nodoEliminar->izquierda == NULL)
	{
		nodoEliminar = NULL;
	}
	//si tiene dos hijos
	if (nodoEliminar->izquierda && nodoEliminar->derecha )
	{
		Nodo *menor = Minimo(nodoEliminar->derecha);
		nodoEliminar->dato = menor->dato;
		EliminarNodoEncontrado(menor);
	}
	else if (nodoEliminar->izquierda)
	{
		Reemplazar(nodoEliminar, nodoEliminar->izquierda);
		DestruirNodo(nodoEliminar);
	}
	else if (nodoEliminar->derecha)
	{
		Reemplazar(nodoEliminar, nodoEliminar->derecha);
		DestruirNodo(nodoEliminar);
	}
	else//si no tiene hijos por ende es hoja
	{
		Reemplazar(nodoEliminar, NULL);
		DestruirNodo(nodoEliminar);
	}
}

void EliminarNodo(Nodo *&arbol, int n)
{
	if (arbol == NULL)
	{
		return;
	}
	else if (n < arbol->dato)
	{
		EliminarNodo(arbol->izquierda, n);
	}
	else if (n > arbol->dato)
	{
		EliminarNodo(arbol->derecha, n);
	}
	else
	{
		EliminarNodoEncontrado(arbol);
	}
}

void RecorridoPreOrden(Nodo *arbol)
{
	if (arbol == NULL)
	{
		return;
	}
	else
	{
		cout<<"\t\t\t\t\t"<<arbol->dato<<"-";
		RecorridoPreOrden(arbol->izquierda);
		RecorridoPreOrden(arbol->derecha);
	}
}

void RecorridoInOrden(Nodo *arbol)
{
	if (arbol == NULL)
	{
		return;
	}
	else
	{
		RecorridoInOrden(arbol->izquierda);
		cout<<"\t\t\t\t\t"<<arbol->dato<<"-";
		RecorridoInOrden(arbol->derecha);
	}
}

void RecorridoPosOrden(Nodo *arbol)
{
	if (arbol == NULL)
	{
		return;
	}
	else
	{
		RecorridoInOrden(arbol->izquierda);
		RecorridoInOrden(arbol->derecha);
		cout<<"\t\t\t\t\t"<<arbol->dato<<"-";
	}
}

void Menu(Nodo *&arbol)
{
	int dato, opcion;
	do
	{
		cout<<"\t.:MENU:."<<endl;
		cout<<"\t1.- Insertar Nodo"<<endl;
		cout<<"\t2.- Mostrar Arbol"<<endl;
		cout<<"\t3.- Buscar valor"<<endl;
		cout<<"\t4.- Recorrer en profundidad por Pre Orden"<<endl;
		cout<<"\t5.- Recorrer en profundidad por In Orden"<<endl;
		cout<<"\t6.- Recorrer en profundidad por Pos Orden"<<endl;
		cout<<"\t7.- Eliminar un nodo"<<endl;
		cout<<"\t8.- Salir"<<endl;
		cout<<"\tOpción: ";
		cin>>opcion;
		switch(opcion)
		{
		case 1:
			cout<<"\t\tIngrese el número a almacenar en el arbol: ";
			cin>>dato;
			InsertarNodoArbol(arbol, NULL, dato);
			break;
		case 2:
			MostrarArbol(arbol, 0);
			break;
		case 3:
			cout<<"\t\tValor a buscar: ";
			cin>>dato;
			if (BuscarNodo(arbol, dato))
			{
				cout<<"\t\t\t\tSe encontró el valor en el arbol"<<endl;
			}
			else
			{
				cout<<"\t\t\t\tNo se encontró el valor en el arbol"<<endl;
			}
			break;
		case 4:
			RecorridoPreOrden(arbol);
			cout<<endl;
			break;
		case 5:
			RecorridoInOrden(arbol);
			cout<<endl;
			break;
		case 6:
			RecorridoPosOrden(arbol);
			cout<<endl;
			break;
		case 7:
			cout<<"Indique el nodo que desea eliminar:";
			cin>>dato;
			EliminarNodo(arbol, dato);
			cout<<endl;
			break;
		}
		system("pause");
		system("cls");
	} while(opcion != 8);
}

int main(int argc, char *argv[]) {
	Nodo *arbol = NULL;
	Menu(arbol);
	return 0;
}

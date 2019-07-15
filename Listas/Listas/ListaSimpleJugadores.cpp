#include <iostream>
using namespace std;

//Lista circular

//Nodo que representa a un jugador dentro de la lista de jugadores
struct Player
{
	int score;
	string name;
	Player *siguiente;
};

//Función que inserta un nodo en la lista
void InsertarPlayer(Player *&leaderboard)
{
	//Realizo la consulta al usuario desde aquí mismo
	string name;//su nombre
	int score;//su puntaje
	cout<<"Ingrese nombre de jugador: ";
	cin>>name;
	cout<<"Ingrese puntaje obtenido en la partida: ";
	cin>>score;
	//si el score es igual a cero salgo y no lo guardo en la lista
	if (score == 0) return;
	//creo un nodo del tipo Player y establezco sus valores
	Player *player = new Player();
	player->name = name;
	player->score = score;
	
	//Necesito crear dos auxiliares, uno apuntando al inicio de la lista y otro que quizas use luego
	Player *auxiliarPrimero = leaderboard;
	Player *auxiliarSegundo;
	
	//Mientras exista un nodo primero y el puntaje de ese sea mayor que el puntaje del nuevo...
	//Mayor que para que me añada de forma ordenada de mayor a menor
	while(auxiliarPrimero != NULL && auxiliarPrimero->score > score)
	{
		//realizo las asignaciones, el segundo auxiliar ahora es el primero
		auxiliarSegundo = auxiliarPrimero;
		//y el primero ahora es el siguiente del primero
		auxiliarPrimero = auxiliarPrimero->siguiente;
	}
	
	//si la lista queda igual (porque no entró al WHILE) y por ende está vacía
	if (leaderboard == auxiliarPrimero)
	{
		//la lista ahora es tan solo el nodo creado en la función
		//Este caso ocurre cuando estamso insertando el primer nodo
		leaderboard = player;
	}
	else//si ya hay nodos en la lista
	{
		//el que le sigue del segundo auxiliar es el nodo que creamos en la función
		//pero, fíjense que entra aquí si se recorrió el WHILE
		auxiliarSegundo->siguiente = player;
	}
	//y ahora le digo al nodo que cree que su apuntador al siguiente nodo es el total de la lista
	player->siguiente = auxiliarPrimero;
}

//Mostramos toda la lista de jugadores con sus puntajes
void MostrarMejores(Player *leaderboard)
{
	//Creo un nodo como índice
	Player *actual = new Player();
	//y ese índice se iguala al inicio de la lista
	actual = leaderboard;
	if (actual == NULL)
	{
		//si el nodo que cree no es nada al fin y al cabo... salimos de la función
		return;
	}
	//como no ingresó al IF...
	cout<<"\tBEST SCORES"<<endl;
	//...lo puedo recorrer
	while (actual != NULL)
	{
		//imprimo en pantalla y luego cambio el indice de la posición actual a la siguiente
		cout<<actual->name<<"\t\t\t"<<actual->score<<endl;
		actual = actual->siguiente;
	}
}

//Busca en la lista por puntaje, es similar a la función anterior

bool BuscarEnLista(Player *leaderboard, int score)
{
	//Creamos un nodo para la búsqueda
	Player *actual = new Player();
	actual = leaderboard;
	while (actual != NULL)
	{
		if (actual->score == score)
		{
			//lo encontró
			return true;
		}
		actual = actual->siguiente;
	}
	//si recorre todo el while y nunca salió de la función entonces no lo encontró
	return false;
}

//Sobrecarga de la función anterior para poder buscar por nombre, se trata de igual forma

bool BuscarEnLista(Player *leaderboard, string name)
{
	Player *actual = new Player();
	actual = leaderboard;
	while (actual != NULL)
	{
		if (actual->name == name)
		{
			return true;
		}
		actual = actual->siguiente;
	}
	return false;
}

//Eliminación del nodo por nombre

void EliminarPlayer(Player *&leaderboard, string nombre)
{
	//si hay algo que se pueda eliminar
	if (leaderboard != NULL)
	{
		//Necesito crear dos auxiliares, uno que indique el que debo borrar y el anterior a ese
		Player *aux_borrado = leaderboard;
		Player *anterior = NULL;
		
		//Mientras que lo que haya obtenido el auxiliar de borrado sea distinto a NADA y el nombre sea distinto al
		//que queremos eliminar
		while(aux_borrado != NULL && aux_borrado->name != nombre)
		{
			//ahora el anterior es el que quiero borrar y el que quiero borrar ahora es el siguiente...
			//...tiene la misma intención de usarse como un índice
			anterior = aux_borrado;
			aux_borrado = aux_borrado->siguiente;
		}
		//si luego del WHILE el auxiliar de borrado quedó en NULL es porque no encontró el elemento a borrar
		if (aux_borrado == NULL)
		{
			cout<<"El jugador con ese puntaje no existe en la lista"<<endl;
		}
		//ahora si el anterior es igual a NADA (el primero)
		else if (anterior == NULL)
		{
			//quita el primer elemento de la lista e indica que el primero ahora es el siguiente.
			leaderboard = leaderboard->siguiente;
			delete aux_borrado;//bye byeee
		}
		else//si no es el primero el que hay que eliminar
		{
			//indico que el siguiente del anterior es el siguiente del nodo a borrar (se ve que está entre medio o
			//al final de la lista)
			anterior->siguiente = aux_borrado->siguiente;
			delete aux_borrado;//bye byeee
		}
	}
}

//Sobrecarga de la función anterior, en este caso eliminamos jugadores con un valor en particular

void EliminarPlayer(Player *&leaderboard, int score)
{
	if (leaderboard != NULL)
	{
		Player *aux_borrado = leaderboard;
		Player *anterior = NULL;
		
		while(aux_borrado != NULL && aux_borrado->score != score)
		{
			anterior = aux_borrado;
			aux_borrado = aux_borrado->siguiente;
		}
		if (aux_borrado == NULL)
		{
			cout<<"El jugador con ese puntaje no existe en la lista"<<endl;
		}
		else if (anterior == NULL)
		{
			leaderboard = leaderboard->siguiente;
			delete aux_borrado;
		}
		else
		{
			anterior->siguiente = aux_borrado->siguiente;
			delete aux_borrado;
		}
	}
}

void VaciarLeaderboard(Player *&leaderboard)
{
	while (leaderboard != NULL)
	{
		Player *auxiliar = leaderboard;
		leaderboard = auxiliar->siguiente;
		delete auxiliar;
	}
}

//Función que realiza un recorrido y obtiene la cantidad de nodos que contiene

int CantidadJugadores(Player *leaderboard)
{
	int acumulador = 0;
	Player *auxiliar = leaderboard;
	while (auxiliar != NULL)
	{
		acumulador++;
		auxiliar = auxiliar->siguiente;
	}
	delete auxiliar;
	return acumulador;
}

//Cuerpo de la función principal del programa

int main(int argc, char *argv[]) {
	Player *leaderboard = NULL;
	char sigue;
	do
	{
		InsertarPlayer(leaderboard);
		system("cls");
		cout<<"Desea agregar otro jugador? (S/N): ";
		cin>>sigue;
		system("cls");
	} while(sigue == 's' || sigue == 'S');
	cout<<"Jugadores: "<<CantidadJugadores(leaderboard)<<endl<<endl;
	MostrarMejores(leaderboard);
	system("pause");
	EliminarPlayer(leaderboard, 10);
	cout<<"Eliminado quien tiene 10 score"<<endl;
	system("pause");
	EliminarPlayer(leaderboard, "Nicolas");
	cout<<"Eliminado Nicolas"<<endl;
	system("pause");
	cout<<"Jugadores (se eliminaron dos antes): "<<CantidadJugadores(leaderboard)<<endl<<endl;
	MostrarMejores(leaderboard);
	system("pause");
	cout<<"Se vacía la lista a continuacion"<<endl;
	VaciarLeaderboard(leaderboard);
	cout<<"Cantidad de nodos luego de su borrado: "<<CantidadJugadores(leaderboard);
	return 0;
}


#include "pch.h"
#include "Highscores.h"

Highscores::Highscores()
{
	Texture t;
	t.loadFromFile("..\\assets\\background.jpg");
	//el tama�o de la pantalla lo obtengo del tama�o de la imagen que uso de fondo
	window = new RenderWindow(VideoMode(t.getSize().x, t.getSize().y), "High Score!");
	background = new Sprite(t);
	evt = new Event();
	leaderboard = NULL;//inicializo la lista en NULL (o sea est� vac�a)
	LlenarLista();//LLamo al m�todo de llenado de lista
	punteroMouse = new Pointer();
	Update();//Luego de todo lo anterior entrego el control del juego al m�todo Update
}

void Highscores::Update()
{
	while (window->isOpen())
	{
		ProcessEvents();//Desde este m�todo se llamar� al de eliminaci�n (si corresponde) de un nodo
		window->clear();
		window->draw(*background);
		//siempre y cuando la lista tenga algo distinto a NULL
		if (leaderboard != NULL)
		{
			MostrarLista();//llamo al m�todo mostrar lista, lo hago con m�todo para facilitar la lectura y
							//no hacer un m�todo muy extenso
		}
		window->draw(punteroMouse->GetSprite());
		window->display();
	}
}

void Highscores::ProcessEvents()
{
	while (window->pollEvent(*evt))
	{
		if (evt->type == Event::Closed)
		{
			window->close();
		}
		if (evt->type == Event::MouseButtonReleased && evt->mouseButton.button == Mouse::Left)
		{
			ControlarColision();//ac� se realizar� un recorrido de la lista
		}
		if (evt->type == Event::MouseMoved)
		{
			(evt->mouseMove.y < 0) ? window->setMouseCursorVisible(true) : window->setMouseCursorVisible(false);
			Vector2f posicion;
			posicion.x = evt->mouseMove.x;
			posicion.y = evt->mouseMove.y;
			punteroMouse->Update(posicion);
		}
	}
}

void Highscores::LlenarLista()
{
	//Ejecuto el m�todo InsertarPlayer 5 veces (o sea, mando a crear 5 nodos que representan al player)
	InsertarPlayer("Juan", 200);
	InsertarPlayer("Rodolfo", 250);
	InsertarPlayer("Epifanio", 130);
	InsertarPlayer("TheMasWinner", 251);
	InsertarPlayer("TheMenosWinner", 20);
}

//El m�todo recibe el nombre del jugador y su puntaje obtenido

void Highscores::InsertarPlayer(string name, int score)
{
	//Creo un Player y le paso su nombre y puntaje
	Player *player = new Player(name, score);
	//Necesito crear dos auxiliares, el primero que apunte al principio de la lista y el otro...
	Player *firstAuxiliar = leaderboard;
	//...lo dejo en NULL para utilizarlo luego
	Player *secondAuxiliar = NULL;
	//Mientras exista un primer nodo y el puntaje del primer nodo sea mayor que el puntaje que recibe el m�todo...
	while (firstAuxiliar != NULL && firstAuxiliar->score > score)
	{
		//Realizo los intercambios, ahora el segundo auxiliar apunta al inicio de la lista...
		secondAuxiliar = firstAuxiliar;
		//y el primer auxiliar apunta a cual era el siguiente de la lista originalmente
		firstAuxiliar = firstAuxiliar->siguiente;
		//este ciclo nos permite ordenar los nodos para se ordenen de mayor a menor, si nos interesa que
		//ingresen de menor a mayor cambiamos el operador de comparaci�n en el WHILE por MENOR QUE
	}
	//Bien, si nunca se realizo el WHILE anterior entonces...
	if (leaderboard == firstAuxiliar)
	{
		leaderboard = player;//...la lista vale al �nico nodo insertado
	}
	else//en el caso que se haya ejecutado el WHILE porque hab�a elementos en la estructura de datos...
	{
		//...el siguiente del segundo auxiliar que se le cargaron elementos en el WHILE apunta al nodo creado
		secondAuxiliar->siguiente = player;
	}
	//y finalmente, el siguiente del nodo creado apunta al resultante de la manipulaci�n del primer auxiliar
	player->siguiente = firstAuxiliar;
	//De este modo logramos insertar un nodo a la estructura de datos de forma ordenada seg�n su valor de score
}

/*
	M�todo que elimina un jugador (o nodo) seg�n el nombre del mismo y reordena la lista
*/

void Highscores::EliminarPlayer(Text *text)
{
	//Si hay nodos en la lista...
	if (leaderboard != NULL)
	{
		//...se crean dos auxiliares, el primero que apunta al principio de la lista...
		Player *auxiliarBorrado = leaderboard;
		//...y el segundo para utilizar luego si es necesario...
		Player *referenciaAnterior = NULL;

		//Mientras exista algo en la lista y que ademas el nombre del nodo sea distinto al texto recibido por el m�todo...
		while (auxiliarBorrado != NULL && auxiliarBorrado->textoName != text)
		{
			//empezamos a recordar cual es el anterior para realizar los intercambios y recorrer la lista
			referenciaAnterior = auxiliarBorrado;
			//ahora decimos que el auxiliar para borrar es el siguiente del auxiliar a borrar (o siguiente en la lista)
			auxiliarBorrado = auxiliarBorrado->siguiente;
			//y esto se va a ejecutar hasta que el texto recibido sea igual al de alg�n texto de un nodo de la lista
		}
		//para no hacer perder el tiempo al pobre m�todo... si el auxiliar de borrado es igual a NULL...
		if (auxiliarBorrado == NULL)
		{
			return;//le indico que la ejecuci�n del m�todo termina ac� porque no hay nada m�s que hacer... ni que borrar
		}
		else if (referenciaAnterior == NULL)//en cambio, si este auxiliar vale algo es porque NO se recorri� el WHILE...
		{
			//y aparentemente el elemento a eliminar es el primero...
			leaderboard = leaderboard->siguiente;//por ende ahora el primero es el siguiente del primero que...
			delete auxiliarBorrado;//...ahora elimino
		}
		else//finalmente, si el nodo a eliminar no es el primero...
		{
			//el anterior que recordaba el nodo a eliminar, ahora recuerda al siguiente del nodo a eliminar...
			referenciaAnterior->siguiente = auxiliarBorrado->siguiente;
			//y finalmente, elimino formalmente de la memoria al nodo a eliminar que estaba entre medio de la
			//instrucci�n anterior
			delete auxiliarBorrado;
		}
	}
}

/*

Con este m�todo realizo un recorrido de los nodos de la lista para determinar si el mouse se est� posando
sobre el tachito de basura de un nodo... ESTE M�TODO SE EJECUTA SOLO CUANDO EL USUARIO REALIZA UN CLICK
NO TIENE NINGUN SENTIDO REALIZARLO TODO EL TIEMPO

*/

void Highscores::ControlarColision()
{
	Player *actual = leaderboard;//utilizo este puntero para conocer cual es el primer nodo de la lista
	FloatRect cajaMouse = punteroMouse->GetSprite().getGlobalBounds();
	while (actual != NULL)//mientras exista algo en lista...
	{
 		FloatRect cajaTrash = actual->spriteTrash->getGlobalBounds();//creo una variable para contener el FloatRect del tachito del nodo actual
		if (cajaMouse.intersects(cajaTrash))//si estan colisionando el puntero del mouse y el tacho...
		{
			EliminarPlayer(actual->textoName);//ejecuto el m�todo EliminarPlayer con el texto del nodo a eliminar
			return;//salgo porque no tiene m�s sentido continuar la ejecuci�n del m�todo
		}
		else//si la colisi�n no se di� con el elemento actual ahora digo que actual es el siguiente de la lista
		{
			//para realizar comprobaci�n con otro nodo
			actual = actual->siguiente;
		}
	}
	//si sali� del WHILE es porque hicimos click en cualquier otra cosa... por ende no ocurre nada...
}

/*

M�todo similar al de control de colsi�n pero, en este caso para obtener las propiedades de un nodo
y dibujarlas con SFML en la pantalla. Contiene ajustes de visualizaci�n para mantener ordenados los puntajes,
nombres de jugadores y tachitos de basura (que no los confundan).

*/
void Highscores::MostrarLista()
{
	Player *actual = leaderboard;//nuevamente me planto sobre el primer nodo de la lista...
	Vector2f posicion;
	posicion.x = window->getSize().x / 6;
	posicion.y = window->getSize().y / 6;
	while (actual != NULL)//mientras exista alg�n nodo en mi auxiliar...
	{
		actual->textoName->setPosition(posicion);//establezco la posici�n del texto del nombre del jugador
		posicion.x = window->getSize().x * 0.7f;
		actual->textoScore->setPosition(posicion);//la del puntaje...
		posicion.x = window->getSize().x * 0.9f;
		actual->spriteTrash->setPosition(posicion);//... la del tacho de basura
		window->draw(*actual->textoName);//dibujo el nombre
		window->draw(*actual->textoScore);//el puntaje
		window->draw(*actual->spriteTrash);//y el tacho
		posicion.x = window->getSize().x / 6;//reseteo los valores de posici�n de mi Vector2f
		posicion.y += window->getSize().y / 7;
		actual = actual->siguiente;//y ahora apunto al siguiente de la lista
	}
}
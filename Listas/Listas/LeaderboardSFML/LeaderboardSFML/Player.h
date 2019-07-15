#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Highscores.h"

using namespace std;
using namespace sf;

/*
Clase Player que representa a un nodo de igual forma que en los ejemplos anteriores, en este caso
un nodo contiene el texto donde se contiene el nombre del jugador, la fuente para mostrarlo, el sprite
que representa al tacho de basura para eliminarlo, el valor de puntaje del jugador y para simplificar las
cosas (como siempre les digo en los Hangouts): indico que es una clase amiga de Highscores
*/

class Player
{
private:
	Font *fuente;
	Text *textoName;
	Text *textoScore;
	Sprite *spriteTrash;
	string nombre;
	int score;
	friend class Highscores;
public:
	//Mediante el constructor indico cual es el "look" del nodo...
	Player(string name, int score)
	{
		fuente = new Font();
		fuente->loadFromFile("..\\assets\\arial.ttf");
		nombre = name;
		this->score = score;
		textoName = new Text();
		textoName->setFont(*fuente);
		textoName->setString(nombre);
		textoScore = new Text();
		textoScore->setFont(*fuente);
		textoScore->setString(to_string(score));
		Texture *tex = new Texture();
		tex->loadFromFile("..\\assets\\trash.png");
		spriteTrash = new Sprite(*tex);
	}
	Player *siguiente;//y recordemos que los nodos siempre tienen como propiedad el puntero al siguiente nodo
};
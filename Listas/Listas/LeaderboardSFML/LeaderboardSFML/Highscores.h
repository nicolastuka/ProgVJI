#pragma once
#include "pch.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Pointer.h"

using namespace sf;

class Highscores
{
private:
	RenderWindow *window;
	Sprite *background;
	Pointer *punteroMouse;
	Event *evt;
	Player *leaderboard;//nuestra lista
	void Update();
	void ProcessEvents();
	void InsertarPlayer(string name, int score);//método que inserta un nodo a la lista con el nombre del jugador y su puntaje obtenido
	void EliminarPlayer(Text *text);//método que elimina un nodo de la lista
	void MostrarLista();//método que muestra cada nodo de la lista
	void LlenarLista();//método que llama 5 veces a InsertarPlayer para llenar la lista inicial
	void ControlarColision();//método para controlar el click del mouse sobre los tachitos de basura
public:
	//Constructor simple
	Highscores();
};
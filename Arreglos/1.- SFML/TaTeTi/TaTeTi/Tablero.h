#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class Tablero {
private:
	RenderWindow *ventana;
	Event *evt;
	RectangleShape lines[4];
	CircleShape circles[9];
	int jugadas = 0;
	bool juegaAzul = true;
	int tablero[3][3];
	void Update();
	void EstablecerFicha(CircleShape circle);
	void VerificarJugada();
public:
	Tablero();
	~Tablero();
};
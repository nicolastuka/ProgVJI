#pragma once
#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Nota.h"

using namespace sf;

class Piano
{
private:
	RenderWindow *w;
	Nota *pilaNotas;//pilas
	Nota *primerNota;//cola
	Nota *ultimaNota;//cola
	SoundBuffer buffer;
	Sound tecla;
	Event evt;
	Sprite s;
	Font fuente;
	Text descripcion;
	void Update();
	void PushNota(Nota *n);//pila
	void PopNota();//pila
	void InsertarNota(int numNota);//cola
	void RemoverNota();//cola
	void LoadNotas();//carga la cola inicial
	void UpdatePila();
	void UpdateCola();
public:
	Piano();
};
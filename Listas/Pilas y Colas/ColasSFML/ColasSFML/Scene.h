#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Coin.h"

using namespace sf;

class Scene
{
private:
	RenderWindow *w;
	Event evt;
	Coin *primerCoin;
	Coin *ultimoCoin;
	Sprite *coinRemovido;
	Text indicadores[8];
	void Update();
	void UpdateCola();
	void ProcessEvents();
	void InsertCoin(int x);
	void RemoveCoin();
	void LoadCola();
public:
	Scene(int w, int h, std::string title);
};
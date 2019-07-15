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
	Coin *pilaCoin;
	Sprite *coinObtenidoEnPop;
	Text indicadores[8];
	void Update();
	void UpdatePila();
	void ProcessEvents();
	void PushCoin(int x);
	void PopCoin();
	void LoadPila();
public:
	Scene(int w, int h, std::string title);
};
#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"

using namespace sf;

class Coin
{
private:
	friend class Scene;
	Texture *t;
	Sprite *s;
public:
	Coin(int posX, int posY)
	{
		t = new Texture();
		t->loadFromFile("..\\assets\\coin.png");
		s = new Sprite(*t);
		s->setPosition(posX, posY);
	}
	Coin *nextCoin;
};
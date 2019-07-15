#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Entity {
private:
	Texture *tex;
	Sprite *spr;
	Font *font;
	Text *text;
	int valueInt;
	string GenerateValueString();
public:
	Entity(int pos);
	~Entity();
	void Draw(RenderWindow *w);
	int GetValue();
	void SetPosition(int newPos);
};
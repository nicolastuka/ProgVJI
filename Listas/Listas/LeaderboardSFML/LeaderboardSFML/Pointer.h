#pragma once
#include <SFML/Graphics.hpp>
#include "pch.h"

using namespace sf;

/*
Clase para manipular el puntero de mouse... no va al caso para el tema que nos compete, es simplemente implementado
por funcionalidad.
*/

class Pointer
{
private:
	Texture *texture;
	Sprite *sprite;
public:
	Pointer();
	void Update(Vector2f position);
	Sprite GetSprite();
};
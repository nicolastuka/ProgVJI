#include "pch.h"
#include "Pointer.h"

/*
Comentarios en archivo de cabecera de clase
*/

Pointer::Pointer()
{
	texture = new Texture();
	texture->loadFromFile("..\\assets\\pointer.png");
	sprite = new Sprite(*texture);
	sprite->setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
}

void Pointer::Update(Vector2f position)
{
	sprite->setPosition(position);
}

Sprite Pointer::GetSprite()
{
	return *sprite;
}
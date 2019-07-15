#include "Entity.h"

Entity::Entity(int pos) {
	tex = new Texture();
	tex->loadFromFile("assets/jurado.png");
	spr = new Sprite(*tex);
	spr->setPosition(pos * tex->getSize().x, 350 - tex->getSize().y);
	font = new Font();
	font->loadFromFile("assets/arial.ttf");
	text = new Text();
	text->setFont(*font);
	text->setString(GenerateValueString());
	text->setCharacterSize(42);
	text->setFillColor(Color::Red);
	text->setPosition(pos * tex->getSize().x + 50, spr->getPosition().y + 30);
}

Entity::~Entity() {
	delete tex;
	delete spr;
}

void Entity::Draw(RenderWindow *w) {
	w->draw(*spr);
	w->draw(*text);
}

string Entity::GenerateValueString() {
	stringstream ss;
	valueInt = rand() % 100;
	ss << valueInt;
	return ss.str();
}

int Entity::GetValue() {
	return valueInt;
}
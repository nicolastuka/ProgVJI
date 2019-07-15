#include "Scene.h"

Scene::Scene(int w, int h, std::string title)
{
	this->w = new RenderWindow(VideoMode(w, h), title);
	coinObtenidoEnPop = NULL;

	Font fuente;
	fuente.loadFromFile("..\\assets\\Arial.ttf");
	indicadores[0].setFont(fuente);
	indicadores[0].setFillColor(Color::Green);
	indicadores[0].setString("10");
	indicadores[0].setPosition(10, 0);
	for (int i = 1; i < 8; i++)
	{
		indicadores[i].setFont(fuente);
		indicadores[i].setFillColor(Color::Green);
		indicadores[i].setString(std::to_string(i * 100));
		indicadores[i].setPosition(i * 100, 0);
	}

	LoadPila();
	Update();
}

void Scene::Update()
{
	while (w->isOpen())
	{
		ProcessEvents();
		UpdatePila();
		w->clear();
		if (coinObtenidoEnPop != NULL)
		{
			w->draw(*coinObtenidoEnPop);
		}
		for (int i = 0; i < 8; i++)
		{
			w->draw(indicadores[i]);
		}
		w->display();
	}
}

void Scene::ProcessEvents()
{
	while (w->pollEvent(evt))
	{
		if (evt.type == Event::Closed)
		{
			w->close();
		}
	}
}

void Scene::PushCoin(int x)
{
	Coin *newCoin = new Coin(x, w->getSize().y);
	newCoin->nextCoin = pilaCoin;
	pilaCoin = newCoin;
}

void Scene::PopCoin()
{
	Coin *aux = pilaCoin;
	coinObtenidoEnPop = aux->s;
	pilaCoin = aux->nextCoin;
	delete aux;
}

void Scene::LoadPila()
{
	PushCoin(10);
	PushCoin(100);
	PushCoin(200);
	PushCoin(300);
	PushCoin(400);
	PushCoin(500);
	PushCoin(600);
	PushCoin(700);
}

void Scene::UpdatePila()
{
	if (coinObtenidoEnPop == NULL && pilaCoin != NULL)
	{
		PopCoin();
	}
	else if (coinObtenidoEnPop != NULL && coinObtenidoEnPop->getPosition().y > -100)
	{
		coinObtenidoEnPop->setPosition(coinObtenidoEnPop->getPosition().x, coinObtenidoEnPop->getPosition().y - 2);
	}

	if (coinObtenidoEnPop != NULL && coinObtenidoEnPop->getPosition().y < 0)
	{
		delete coinObtenidoEnPop;
		coinObtenidoEnPop = NULL;
	}
}
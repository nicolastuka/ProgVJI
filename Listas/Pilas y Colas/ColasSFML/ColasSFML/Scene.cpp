#include "Scene.h"

Scene::Scene(int w, int h, std::string title)
{
	this->w = new RenderWindow(VideoMode(w, h), title);
	coinRemovido = NULL;
	primerCoin = NULL;
	ultimoCoin = NULL;
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

	LoadCola();
	Update();
}

void Scene::Update()
{
	while (w->isOpen())
	{
		ProcessEvents();
		UpdateCola();
		w->clear();
		if (coinRemovido != NULL)
		{
			w->draw(*coinRemovido);
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

void Scene::InsertCoin(int x)
{
	Coin *newCoin = new Coin(x, w->getSize().y);
	newCoin->nextCoin = NULL;
	if (primerCoin == NULL)
	{
		primerCoin = newCoin;
	}
	else
	{
		ultimoCoin->nextCoin = newCoin;
	}
	ultimoCoin = newCoin;
}

void Scene::RemoveCoin()
{
	coinRemovido = primerCoin->s;
	Coin *aux = primerCoin;
	if (primerCoin == ultimoCoin)
	{
		primerCoin = NULL;
		ultimoCoin = NULL;
	}
	else
	{
		primerCoin = primerCoin->nextCoin;
	}
	delete aux;
}

void Scene::LoadCola()
{
	InsertCoin(10);
	InsertCoin(100);
	InsertCoin(200);
	InsertCoin(300);
	InsertCoin(400);
	InsertCoin(500);
	InsertCoin(600);
	InsertCoin(700);
}

void Scene::UpdateCola()
{
	if (coinRemovido == NULL && primerCoin != NULL)
	{
		RemoveCoin();
	}
	else if (coinRemovido != NULL && coinRemovido->getPosition().y > -100)
	{
		coinRemovido->setPosition(coinRemovido->getPosition().x, coinRemovido->getPosition().y - 2);
	}

	if (coinRemovido != NULL && coinRemovido->getPosition().y < 0)
	{
		delete coinRemovido;
		coinRemovido = NULL;
	}
}
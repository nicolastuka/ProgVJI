#include "Scene.h"

Scene::Scene(int width, int height, string title) {
	window = new RenderWindow(VideoMode(width, height), title);
	window->setFramerateLimit(60);
	evt = new Event();

	LoadVectorEntities();

	int promedio = 0;
	for (int i = 0; i < 3; i++) {
		promedio += e[i]->GetValue();
	}
	promedio /= 3;

	font = new Font();
	font->loadFromFile("assets/arial.ttf");

	textPromedio = new Text();
	textPromedio->setFont(*font);
	textPromedio->setFillColor(Color::White);
	textPromedio->setCharacterSize(72);
	textPromedio->setPosition(0, 50);

	textPromedio->setString(GetPromedioString(promedio));

	Update();
}

Scene::~Scene() {
	delete window;
}

void Scene::Update() {
	while (window->isOpen())
	{
		ProcessEvents();
		window->clear();
		for (int i = 0; i < 3; i++) {
			e[i]->Draw(window);
		}
		window->draw(*textPromedio);
		window->display();
	}
}

void Scene::ProcessEvents() {
	while (window->pollEvent(*evt)) {
		if (evt->type == Event::Closed) {
			window->close();
		}
	}
}

void Scene::LoadVectorEntities() {
	for (int i = 0; i < 3; i++) {
		e[i] = new Entity(i);
	}
}

string Scene::GetPromedioString(int promedio) {
	stringstream ss;
	ss << "Promedio: " << promedio;
	return ss.str();
}
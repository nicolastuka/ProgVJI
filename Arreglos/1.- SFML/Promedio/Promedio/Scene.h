#pragma once

#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Entity.h"

using namespace std;
using namespace sf;

class Scene {
private:
	RenderWindow *window;
	Event *evt;
	Entity *e[3];
	Font *font;
	Text *textPromedio;
	void Update();
	void ProcessEvents();
	void LoadVectorEntities();
	string GetPromedioString(int promedio);
public:
	Scene(int width, int height, string title);
	~Scene();
};

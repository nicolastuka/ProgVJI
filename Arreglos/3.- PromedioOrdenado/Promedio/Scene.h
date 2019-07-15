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
	Entity *e[6];//4.- el vector de entidades (jurado con cartelito y valor)
	/*  5.- un vector que se carga los valores enteros de las entidades, sirve para probar el ordenamiento 
		de forma rápida nomas, acuerdense del Hangout
	*/
	int valuesEntities[6];
	Font *font;
	Text *textPromedio;
	Text *textInstructions;
	Text *textMethodSelected;
	void Update();
	void ProcessEvents();
	void LoadVectorEntities();//6.- método que carga el vector de entidades y el vector numerico
	string GetPromedioString(int promedio);//7.- obtiene la cadena "Promedio: " con el valor
	//8.- Los métodos de ordenamiento
	void OrderByBubble();
	void OrderByInsertion();
	void OrderBySelection();
	//8.1- ATENCIÓN: este me parece que no les dije que es un método recursivo (se llama así mismo vean la implementación)
	void OrderByQuicksort(int *arreglo, int izquierda, int derecha);
	bool reset = false;//9.- nada no es importante, es el control del RESET --> continúo la lectura de la implementación de 
						//la clase (Scene.cpp)
public:
	//1.- fíjense que siempre mantengo la idea de que la aplicación se maneje sola
	Scene(int width, int height, string title);
	~Scene();
	bool isReset();//2.- Excepto por esto que me vuelve a levantar la ventana

	//3.- Esta forma de resetear el juego no es la adecuada y para nada es prolija... pero es rápida

};

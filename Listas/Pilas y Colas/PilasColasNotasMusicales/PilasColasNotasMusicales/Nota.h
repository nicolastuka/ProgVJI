#pragma once
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;

class Nota
{
private:
	friend class Piano;
	SoundBuffer sonido;
	std::string nombre;
public:
	Nota(int numNota)
	{
		switch (numNota)
		{
		case 0:
			sonido.loadFromFile("..\\assets\\do.wav");
			nombre = "DO";
			break;
		case 1:
			sonido.loadFromFile("..\\assets\\re.wav");
			nombre = "RE";
			break;
		case 2:
			sonido.loadFromFile("..\\assets\\mi.wav");
			nombre = "MI";
			break;
		case 3:
			sonido.loadFromFile("..\\assets\\fa.wav");
			nombre = "FA";
			break;
		case 4:
			sonido.loadFromFile("..\\assets\\sol.wav");
			nombre = "SOL";
			break;
		case 5:
			sonido.loadFromFile("..\\assets\\la.wav");
			nombre = "LA";
			break;
		case 6:
			sonido.loadFromFile("..\\assets\\si.wav");
			nombre = "SI";
			break;
		default:
			break;
		}
	}
	Nota *siguiente;
};
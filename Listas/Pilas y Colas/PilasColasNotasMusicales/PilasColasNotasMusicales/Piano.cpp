#include "pch.h"
#include "Piano.h"

Piano::Piano()
{
	Texture texture;
	texture.loadFromFile("..\\assets\\ludwing.jpg");
	Image img;
	img.loadFromFile("..\\assets\\ludwing.jpg");
	w = new RenderWindow(VideoMode(texture.getSize().x, texture.getSize().y), "Pilas y Colas Musicales");	
	w->setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());
	s.setTexture(texture);

	pilaNotas = NULL;

	primerNota = NULL;
	ultimaNota = NULL;
	
	Update();
}

void Piano::Update()
{
	while (w->isOpen())
	{
		while (w->pollEvent(evt))
		{
			if (evt.type == Event::Closed)
			{
				w->close();
			}
		}
		if (pilaNotas == NULL && primerNota == NULL && ultimaNota == NULL)
		{
			LoadNotas();
		}
		UpdateCola();
		UpdatePila();
		w->clear();
		w->draw(s);
		w->draw(descripcion);
		w->display();
	}
}

void Piano::PopNota()
{
	Nota *auxiliar = pilaNotas;
	pilaNotas = auxiliar->siguiente;
	buffer = auxiliar->sonido;
	w->setTitle("Pila -> " + auxiliar->nombre);
	delete auxiliar;
}

void Piano::PushNota(Nota *n)
{
	n->siguiente = pilaNotas;
	pilaNotas = n;
}

void Piano::LoadNotas()
{
	InsertarNota(0);
	InsertarNota(1);
	InsertarNota(2);
	InsertarNota(3);
	InsertarNota(4);
	InsertarNota(5);
	InsertarNota(6);
}

void Piano::InsertarNota(int numNota)
{
	Nota *nota = new Nota(numNota);
	nota->siguiente = NULL;
	if (primerNota == NULL)
	{
		primerNota = nota;
	}
	else
	{
		ultimaNota->siguiente = nota;
	}
	ultimaNota = nota;
}

void Piano::RemoverNota()
{
	Nota *auxiliar = primerNota;
	if (primerNota == ultimaNota)
	{
		primerNota = NULL;
		ultimaNota = NULL;
	}
	else
	{
		primerNota = primerNota->siguiente;
	}
	//El nodo, en lugar de eliminarlo lo paso a otra estructura de datos.
	PushNota(auxiliar);
	buffer = auxiliar->sonido;
	w->setTitle("Cola -> " + auxiliar->nombre);
	//No corresponde porque sino estaríamos eliminando la referencia a la nota que pasa a la pila
	delete auxiliar;
	//si fuese necesario pasar de la pila a la cola tampoco deberíamos realizar la eliminación
}

void Piano::UpdateCola()
{
	if (primerNota != NULL)
	{
		if (tecla.getStatus() == tecla.Stopped)
		{
			RemoverNota();
			tecla.setBuffer(buffer);
			tecla.play();
		}
	}
}

void Piano::UpdatePila()
{
	if (pilaNotas != NULL)
	{
		if (tecla.getStatus() == tecla.Stopped)
		{
			PopNota();
			tecla.setBuffer(buffer);
			tecla.play();
		}
	}
}
#include "Tablero.h"

Tablero::Tablero() {
	ventana = new RenderWindow(VideoMode(400, 400), "Ta Te Ti");
	ventana->setFramerateLimit(60);
	evt = new Event();

	ventana->setTitle("Ta Te Ti - Juega Azul");

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tablero[i][j] = 0;
		}
	}
	
	for (int i = 0; i < 4; i++) {
		lines[i] = RectangleShape(Vector2f(400, 2));
		lines[i].setFillColor(Color::Black);
	}

	lines[0].setPosition(Vector2f(0, 400 * 0.33f));
	lines[1].setPosition(Vector2f(0, 400 * 0.66f));
	lines[2].setRotation(90);
	lines[2].setPosition(Vector2f(400 * 0.33f, 0));
	lines[3].setRotation(90);
	lines[3].setPosition(Vector2f(400 * 0.66f, 0));

	Update();
}

Tablero::~Tablero() {
	delete evt;
	delete ventana;
}

void Tablero::Update() {
	while (ventana->isOpen()) {
		while (ventana->pollEvent(*evt)) {
			if (evt->type == Event::Closed && jugadas == 0) {
				ventana->close();
				exit(EXIT_SUCCESS);
			}
			if (evt->type == Event::MouseButtonReleased) {
				if (evt->mouseButton.button == sf::Mouse::Left) {
					CircleShape circle = CircleShape(50);
					if (juegaAzul) {
						circle.setFillColor(Color::Blue);
						ventana->setTitle("Ta Te Ti - Juega Rojo");
					} else {
						circle.setFillColor(Color::Red);
						ventana->setTitle("Ta Te Ti - Juega Azul");
					}
					if (jugadas > 8) {
						return;
					}
					circle.setPosition(evt->mouseButton.x, evt->mouseButton.y);
					EstablecerFicha(circle);
				}
			}
		}
		ventana->clear(Color::White);
		for (int i = 0; i < 4; i++) {
			ventana->draw(lines[i]);
		}
		for (int i = 0; i < 9; i++) {
			ventana->draw(circles[i]);
		}
		ventana->display();
	}
}

void Tablero::EstablecerFicha(CircleShape circle) {
	int x, y;
	if (circle.getPosition().x > 0 && circle.getPosition().x < 400 * 0.33f) x = 0;
	if (circle.getPosition().x > 400 * 0.33f && circle.getPosition().x < 400 * 0.66f) x = 1;
	if (circle.getPosition().x > 400 * 0.66f && circle.getPosition().x < 400) x = 2;
	if (circle.getPosition().y > 0 && circle.getPosition().y < 400 * 0.33f) y = 0;
	if (circle.getPosition().y > 400 * 0.33f && circle.getPosition().y < 400 * 0.66f) y = 1;
	if (circle.getPosition().y > 400 * 0.66f && circle.getPosition().y < 400) y = 2;
	circle.setPosition(Vector2f((x * (400 * 0.33f)) + 15, (y * (400 * 0.33f)) + 15));
	if (tablero[x][y] == 0) {
		circles[jugadas] = circle;
		(juegaAzul) ? tablero[x][y] = 1 : tablero[x][y] = 2;
		jugadas++;
		VerificarJugada();
		juegaAzul = !juegaAzul;
	}
}

void Tablero::VerificarJugada() {
	//horizontales
	for (int i = 0; i < 3; i++) {
		if (tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i])
		{
			if (tablero[0][i] != 0) {
				jugadas = 9;
				(juegaAzul) ? ventana->setTitle("Ta Te Ti - Ganador --> Azul") : ventana->setTitle("Ta Te Ti - Ganador --> Rojo");
				std::cout << "Hay un ganador horizontal" << std::endl;
			}
		}
	}

	//verticales
	for (int i = 0; i < 3; i++) {
		if (tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2])
		{
			if (tablero[i][0] != 0) {
				jugadas = 9;
				(juegaAzul) ? ventana->setTitle("Ta Te Ti - Ganador --> Azul") : ventana->setTitle("Ta Te Ti - Ganador --> Rojo");
				std::cout << "Hay un ganador vertical" << std::endl;
			}
		}
	}

	//diagonales
	if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2])
	{
		if (tablero[0][0] != 0) {
			jugadas = 9;
			(juegaAzul) ? ventana->setTitle("Ta Te Ti - Ganador --> Azul") : ventana->setTitle("Ta Te Ti - Ganador --> Rojo");
			std::cout << "Hay un ganador diagonal identidad" << std::endl;
		}
	}
	if (tablero[2][0] == tablero[1][1] && tablero[1][1] == tablero[0][2])
	{
		if (tablero[2][0] != 0) {
			jugadas = 9;
			(juegaAzul) ? ventana->setTitle("Ta Te Ti - Ganador --> Azul") : ventana->setTitle("Ta Te Ti - Ganador --> Rojo");
			std::cout << "Hay un ganador diagonal inversa" << std::endl;
		}
	}
}
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif

#include "Game.h"
#include <iostream>
#include <stdlib.h>

int main()
{
	srand(time(NULL));
	sf::RectangleShape screenShape;
	sf::Texture loadTexture;
	loadTexture.loadFromFile("Assets\\Sprites\\loading.png");
	screenShape.setSize(sf::Vector2f(GlobalSettings::s_width, GlobalSettings::s_height));
	screenShape.setTexture(&loadTexture);

	
	sf::RenderWindow loadWindow;
	
	loadWindow.create(sf::VideoMode(GlobalSettings::s_width, GlobalSettings::s_height, 32), "Aoife & Eoin Project 3", sf::Style::Default);
	loadWindow.draw(screenShape);
	loadWindow.display();
	
	Game game(loadWindow);
	game.run();
	return 1;
}
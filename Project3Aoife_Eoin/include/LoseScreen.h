#ifndef LOSESCREEN
#define LOSESCREEN

#include "SFML/Graphics.hpp"
#include "ResourceManager.h"

class LoseScreen
{
public:
	LoseScreen(ResourceManager & t_resourceManager);
	~LoseScreen();

	void render(sf::RenderWindow &t_window);

private:
	sf::Text m_loseText;
	sf::Font m_font;
	ResourceManager & m_resourceManager;

};
#endif

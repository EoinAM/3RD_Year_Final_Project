#ifndef HELPCLASS
#define HELPCLASS


#include <iostream>
#include <SFML/Graphics.hpp>
#include "Global.h"

class Help
{
public:
	Help(ResourceManager & t_rm);
	~Help();
	void setUp();
	void draw(sf::RenderWindow &t_window);

private:

	ResourceManager & m_rm;

	sf::Text m_titleText;
	sf::Sprite m_star;
	sf::Sprite m_heart;
	sf::Sprite m_key;
	sf::RectangleShape m_background;
	sf::Text m_text[3];
};


#endif // !HELP
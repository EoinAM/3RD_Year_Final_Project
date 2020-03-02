#ifndef OPTIONSCLASS
#define OPTIONSCLASS


#include <iostream>
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Xbox360Controller.h"

class OptionsScreen
{
public:
	OptionsScreen(ResourceManager & t_rm);
	~OptionsScreen();

	void setUp();
	void update(Xbox360Controller &t_control, sf::Sound &t_music);
	void draw(sf::RenderWindow &t_window);
	ResourceManager & m_rm;

	sf::Text m_mute;
	sf::Font m_font;
	sf::RectangleShape m_muteButton;
};
#endif

#ifndef PAUSE
#define PAUSE

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Xbox360Controller.h"
#include "Global.h"

class Pause
{
public:
	Pause(ResourceManager & t_rm);
	~Pause();

	void setUp(sf::RenderWindow &t_window);
	void draw(sf::RenderWindow &t_window);
	void update(double &d_t, Xbox360Controller & t_controller);
	void moveButton(int t_buttonNum, int t_buttonNum2);

	bool m_switchMainMenu = false;
	bool m_switchPlay = false;

private:
	ResourceManager & m_rm;
	sf::RectangleShape m_background;
	//the maximum amount of buttons
	static const int M_MAX_BUTTON = 2;
	sf::Text m_text[M_MAX_BUTTON];
	sf::String m_buttonString[M_MAX_BUTTON] = { "Resume", "Exit to Main Menu" };
	//the current active button
	int m_currentButton = 0;
	bool m_moved = false;
};

#endif // !PAUSE
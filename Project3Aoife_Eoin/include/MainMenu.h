#ifndef MAINMENUCLASS
#define MAINMENUCLASS


#include <iostream>
#include "SFML/Graphics.hpp"
#include "Xbox360Controller.h"
#include "Global.h"
#include "ResourceManager.h"
#include <SFML\Audio.hpp>


class MainMenu
{
public:
	MainMenu(ResourceManager & t_resMan);
	~MainMenu();

public:
	void setUp();
	void render(sf::RenderWindow &t_window);
	void update(double &d_t, Xbox360Controller & t_controller);
	void moveButton(int t_buttonNum, int t_buttonNum2, int t_buttonNum3, int t_buttonNum4);

	//Public bools used for switching the screen when a button is pressed
	bool m_switchStart = false;
	bool m_switchExit = false;
	bool m_switchHelp = false;
	bool m_switchOptions = false;
	sf::Sound m_music;
private:

	ResourceManager & m_rm;

	//the maximum amount of buttons
	static const int M_MAX_BUTTON = 4;
	sf::Text m_buttonText[M_MAX_BUTTON];
	sf::String m_buttonString[M_MAX_BUTTON] = { "Start", "Help", "Options", "Exit" };
	//the current active button
	int m_currentButton = 0;
	bool m_moved = false;

	sf::RectangleShape m_background;
	sf::SoundBuffer m_musicBuffer;

	int timer = 0;
};


#endif // !MAINMENU

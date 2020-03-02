#ifndef SCENEMANAGER
#define SCENEMANAGER

#include "Global.h"
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "Help.h"
#include "Pause.h"
#include "playScreen.h"
#include "Xbox360Controller.h"
#include "RoomBuilder.h"
#include "OptionsScreen.h"

//enum class to store the screens
enum class GameState
{
	MAINMENU,
	HELP,
	PLAY,
	PAUSES,
	OPTIONS,
	EXIT
};

class SceneManager
{
public:
	SceneManager( ResourceManager & t_resMan, sf::RenderWindow & t_window);
	~SceneManager();

	sf::RenderWindow &m_window;

	Xbox360Controller m_controller;

	sf::View m_normView;

	ResourceManager & m_resourceMan;

	playScreen m_playScreen;
	MainMenu m_mainmenu;
	Help m_helpmenu;
	Pause m_pausemenu;
	OptionsScreen m_optionsMenu;
	static GameState currentState;
	
	void setUp();
	void update(double &t_dt);
	void draw(sf::RenderWindow &t_window);
};

#endif // !SCENEMANAGER

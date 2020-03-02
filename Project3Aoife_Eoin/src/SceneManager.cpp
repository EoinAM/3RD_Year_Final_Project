#include "SceneManager.h"

GameState SceneManager::currentState = GameState::MAINMENU; //current state of game

SceneManager::SceneManager(ResourceManager & t_resMan, sf::RenderWindow & t_window) :
	m_window(t_window),
	m_resourceMan(t_resMan),
	m_playScreen(t_resMan, m_window, m_controller),
	m_mainmenu(t_resMan),
	m_helpmenu(t_resMan),
	m_pausemenu(t_resMan),
	m_optionsMenu(t_resMan)
{
	
	m_normView.setCenter(GlobalSettings::s_width * .5, GlobalSettings::s_height * .5);
	m_normView.setSize(GlobalSettings::s_width, GlobalSettings::s_height);
	m_window.setView(m_normView);
	setUp();

}//!SceneManager

SceneManager::~SceneManager()
{
}//!~SceneManger

//sets up the screens text
void SceneManager::setUp()
{
	m_mainmenu.setUp();
	m_helpmenu.setUp();
	m_pausemenu.setUp(m_window);
	m_optionsMenu.setUp();
}//!setUp

//updates the button scrolling
void SceneManager::update(double &t_dt)
{
	if (m_controller.isConnected())
	{
		m_controller.update();
	}
	else
	{
		m_controller.connect();
	}
	
	switch (currentState)
	{
	default:
		break;
	case GameState::MAINMENU:
		m_window.setView(m_normView);
		m_mainmenu.update(t_dt, m_controller);
		break;
	case GameState::PLAY:
		m_window.setView(m_playScreen.m_gameView);
		m_playScreen.update(t_dt);
		break;
	case GameState::HELP:
		m_window.setView(m_normView);
		break;
	case GameState::PAUSES:
		m_window.setView(m_normView);
		m_pausemenu.update(t_dt, m_controller);
		break;
	case GameState::OPTIONS:
		m_window.setView(m_normView);
		m_optionsMenu.update(m_controller, m_mainmenu.m_music);
		break;
	case GameState::EXIT:
		m_window.setView(m_normView);
		break;

	}//!switch
}//!Update

//draws the screen if it is active
void SceneManager::draw(sf::RenderWindow & t_window)
{
	switch (currentState)
	{
	default:
		break;
	case GameState::MAINMENU:
		m_mainmenu.render(t_window);
		if (m_mainmenu.m_switchStart)
		{
			currentState = GameState::PLAY;
		}//!if

		if (m_mainmenu.m_switchExit)
		{
			currentState = GameState::EXIT;
		}//!if

		if (m_mainmenu.m_switchHelp)
		{
			currentState = GameState::HELP;
		}//!if

		if (m_mainmenu.m_switchOptions)
		{
			currentState = GameState::OPTIONS;
		}//!if

		break;
	case GameState::PLAY:
		m_playScreen.render();
		m_pausemenu.m_switchMainMenu = false;
		if (m_playScreen.m_switchPause)
		{
			m_pausemenu.m_switchPlay = false;
			currentState = GameState::PAUSES;
		}//!if
		break;
	case GameState::HELP:
		m_helpmenu.draw(t_window);
		if (m_controller.m_currentState.B)
		{
			m_mainmenu.m_switchHelp = false;
			currentState = GameState::MAINMENU;
		}//!if
		break;
	case GameState::PAUSES:
		m_pausemenu.draw(t_window);
		if (m_pausemenu.m_switchMainMenu)
		{
			m_playScreen.m_switchPause = false;
			currentState = GameState::MAINMENU;
		}//!if
		if (m_pausemenu.m_switchPlay)
		{
			m_playScreen.m_switchPause = false;
			currentState = GameState::PLAY;
		}//!if
		break;
	case GameState::OPTIONS:
		m_optionsMenu.draw(t_window);
		if (m_controller.m_currentState.B)
		{
			m_mainmenu.m_switchOptions = false;
			currentState = GameState::MAINMENU;
		}//!if
		break;
	case GameState::EXIT:
		t_window.close();
		break;

	}//!switch
}//!end

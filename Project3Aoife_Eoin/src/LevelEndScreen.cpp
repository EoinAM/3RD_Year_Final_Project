#include "LevelEndScreen.h"

LevelEndScreen::LevelEndScreen(RoomBuilder & t_roomBuilder,
	ResourceManager & t_resourceMan, sf::RenderWindow & t_window, Xbox360Controller & t_control) :
	m_resManager(t_resourceMan), m_window(t_window), m_controller(t_control), m_roomBuilder(t_roomBuilder)
{
	m_levelOver_text.setFillColor(sf::Color::White);
	m_levelOver_text.setString(" YOU WIN \n PRESS A TO GO TO RESTART GAME");
	m_levelOver_text.setCharacterSize(50);
	m_levelOver_text.setFont(m_resManager.m_font);
}

LevelEndScreen::~LevelEndScreen()
{
}

void LevelEndScreen::update(float t_dt, Player & t_player)
{
	if (m_isShown)
	{
		if (m_controller.m_currentState.A)
		{
			m_isShown = false;
		}
	}
}

void LevelEndScreen::render()
{
	if (m_isShown)
	{
		m_window.clear(sf::Color::Black);
		m_window.draw(m_levelOver_text);
	}
}

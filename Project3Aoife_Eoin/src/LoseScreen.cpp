#include "LoseScreen.h"


LoseScreen::LoseScreen(ResourceManager & t_resourceManager) : 
	m_resourceManager(t_resourceManager)
{
	m_loseText.setCharacterSize(100);
	m_loseText.setFillColor(sf::Color::Yellow);
	m_loseText.setFont(m_resourceManager.m_font);
	m_loseText.setPosition(600, 400);
	m_loseText.setString("YOU LOSE \n PRESS A TO RESTART THE GAME");
}

LoseScreen::~LoseScreen()
{
}

void LoseScreen::render(sf::RenderWindow & t_window)
{
	t_window.clear(sf::Color::Black);
	t_window.draw(m_loseText);
}

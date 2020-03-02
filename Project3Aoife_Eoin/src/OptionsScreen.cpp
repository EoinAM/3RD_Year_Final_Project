#include "OptionsScreen.h"



OptionsScreen::OptionsScreen(ResourceManager & t_rm):
	m_rm(t_rm),
	m_font(t_rm.m_font)
{
}


OptionsScreen::~OptionsScreen()
{
}

void OptionsScreen::setUp()
{
	m_mute.setCharacterSize(50);
	m_mute.setFillColor(sf::Color::White);
	m_mute.setFont(m_font);
	m_mute.setPosition(500, 200);
	m_mute.setString("Mute");

	m_muteButton.setFillColor(sf::Color::Black);
	m_muteButton.setOutlineColor(sf::Color::White);
	m_muteButton.setOutlineThickness(4);
	m_muteButton.setPosition(525, 300);
	m_muteButton.setSize(sf::Vector2f(50, 50));
}

void OptionsScreen::update(Xbox360Controller & t_control, sf::Sound &t_music)
{
	if (t_control.m_currentState.A)
	{
		m_muteButton.setFillColor(sf::Color::Green);
		t_music.stop();
	}

	if (t_control.m_currentState.B)
	{
		m_muteButton.setFillColor(sf::Color::White);
		t_music.play();
	}
}

void OptionsScreen::draw(sf::RenderWindow & t_window)
{
	t_window.draw(m_mute);
	t_window.draw(m_muteButton);
}

#include "Pause.h"

Pause::Pause(ResourceManager & t_rm):
	m_rm(t_rm)
{
}//!Pause

Pause::~Pause()
{
}//!~Pause

void Pause::setUp(sf::RenderWindow &t_window)
{
	for (int i = 0; i < M_MAX_BUTTON; i++)
	{
		m_text[i].setFont(m_rm.m_font);
		m_text[i].setFillColor(sf::Color::Black);
		m_text[i].setCharacterSize(50);
		m_text[i].setPosition(500, (i * 100) + 100);
		m_text[i].setString(m_buttonString[i]);
	}//!for
	m_background.setSize(sf::Vector2f(GlobalSettings::s_width, GlobalSettings::s_height));
	m_background.setTexture(&m_rm.m_menuBg);

}//!setUp

void Pause::draw(sf::RenderWindow &t_window)
{
	t_window.draw(m_background);
	for (int i = 0; i < M_MAX_BUTTON; i++)
	{
		t_window.draw(m_text[i]);
	}//!for
}//!draw

void Pause::update(double & d_t, Xbox360Controller & t_controller)
{
	//loops the active buttons
	if (m_currentButton > 1)
	{
		m_currentButton = 0;
	}//!if
	if (m_currentButton < 0)
	{
		m_currentButton = 1;
	}//!if

	//checks to see if the key is released before
	//regestering another key press
	if (!m_moved)
	{
		//moves to the next button if key is pressed
		if (t_controller.m_currentState.LeftThumbStick.y >= -15)
		{
			m_currentButton += 1;
			m_moved = true;
		}//!if
		if (t_controller.m_currentState.LeftThumbStick.y <= 15)
		{
			m_currentButton -= 1;
			m_moved = true;
		}//!if
	}//!if
	if (t_controller.m_currentState.LeftThumbStick.y > 0 && t_controller.m_currentState.LeftThumbStick.y < 15 ||
		t_controller.m_currentState.LeftThumbStick.y < 0 && t_controller.m_currentState.LeftThumbStick.y > -15)
	{
		m_moved = false;
	}//!if

	//changes the current button to active
	//and resets the other buttons to normal
	//checks is a button was selected and moves to the respective screen

	if (m_currentButton == 0)
	{
		moveButton(0, 1);
		if (t_controller.m_currentState.A)
		{
			m_switchPlay = true;
		}//!if
	}//!if
	if (m_currentButton == 1)
	{
		moveButton(1, 0);
		if (t_controller.m_currentState.A)
		{
			if (!t_controller.m_previousState.A)
			{
				m_switchMainMenu = true;
			}
		}//!if
	}//!if
}//!update

void Pause::moveButton(int t_buttonNum, int t_buttonNum2)
{
	m_text[t_buttonNum].setFillColor(sf::Color::White);
	m_text[t_buttonNum].setOutlineColor(sf::Color::White);
	m_text[t_buttonNum].setOutlineThickness(2.5);

	m_text[t_buttonNum2].setFillColor(sf::Color::Black);
	m_text[t_buttonNum2].setOutlineThickness(0);
}//!moveButton

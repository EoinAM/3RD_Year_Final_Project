#include "PickUps.h"

PickUps::PickUps(ResourceManager & t_resMan, Xbox360Controller &t_control) :
	m_keyTexture(t_resMan.m_key),
	m_starTexture(t_resMan.m_star),
	m_heartTexture(t_resMan.m_heart),
	m_font(t_resMan.m_font),
	m_controller(t_control)
{
	m_key.setScale(0.2, 0.2);
	m_key.setTexture(m_keyTexture);

	m_star.setScale(0.2, 0.2);
	m_star.setTexture(m_starTexture);

	m_heart.setScale(0.2, 0.2);
	m_heart.setTexture(m_heartTexture);
	setUp();
}

PickUps::~PickUps()
{
}

void PickUps::update(float & t_speed)
{
	if (m_pickedUp)
	{
		if (m_controller.m_currentState.LTrigger > 1)
		{
			m_speedTimerStart = true;
			m_pickedUp = false;
		}
		m_star.setPosition(920, -80);
	}

	if (m_keyOwned)
	{
		m_key.setPosition(700, -80);
	}

	if (m_speedTimerStart)
	{
		m_speedTimer--;
		t_speed = { 4 };
	}
	if (m_speedTimer <= 0)
	{
		m_speedTimerStart = false;
		m_speedTimer = 1000;
		t_speed = { 2 };
	}
}

void PickUps::heartPosition(sf::Vector2f  t_pos)
{
	m_heart.setPosition(t_pos);
	m_heartDropped = true;
}

void PickUps::starPosition(sf::Vector2f  t_pos)
{
	m_star.setPosition(t_pos);
	m_starDropped = true;
}

void PickUps::keyPosition(sf::Vector2f  t_pos)
{
	m_key.setPosition(t_pos);
	m_keyDropped = true;
}

void PickUps::heartCollision()
{
	m_heartDropped = false;
}

void PickUps::starCollision()
{
	m_starDropped = false;
	m_pickedUp = true;
}

void PickUps::keyCollision()
{
	m_keyDropped = false;
	m_keyOwned = true;
}

void PickUps::setUp()
{
	m_lives.setCharacterSize(40);
	m_lives.setFillColor(sf::Color::Red);
	m_lives.setFont(m_font);
	m_lives.setPosition(20, -120);
	m_lives.setString("~ Lives ~");

	m_pressLT.setCharacterSize(20);
	m_pressLT.setFillColor(sf::Color::White);
	m_pressLT.setFont(m_font);
	m_pressLT.setPosition(905, -110);
	m_pressLT.setString("Press LT");

	m_square.setFillColor(sf::Color::Black);
	m_square.setOutlineColor(sf::Color(60,60,60));
	m_square.setOutlineThickness(3);
	m_square.setPosition(900, -110);
	m_square.setSize(sf::Vector2f(100, 100));
}

void PickUps::render(sf::RenderWindow & t_window)
{
	if (m_keyDropped == true)
	{
		t_window.draw(m_key);
	}

	if (m_starDropped == true || m_pickedUp == true)
	{
		t_window.draw(m_star);
	}

	if (m_heartDropped == true)
	{
		t_window.draw(m_heart);
	}
}

void PickUps::HUDrender(sf::RenderWindow & t_window)
{
	t_window.draw(m_lives);
	t_window.draw(m_square);
	t_window.draw(m_pressLT);
}


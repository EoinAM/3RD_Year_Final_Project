#include "Help.h"



Help::Help(ResourceManager & t_rm):
	m_rm(t_rm)
{
	
}//!Help


Help::~Help()
{
}//!~Help

void Help::setUp()
{
	m_titleText.setCharacterSize(80);
	m_titleText.setFillColor(sf::Color::White);
	m_titleText.setFont(m_rm.m_font);
	m_titleText.setPosition(800, 100);
	m_titleText.setString("Help");

	for (int i = 0; i < 3; i++)
	{
		m_text[i].setCharacterSize(30);
		m_text[i].setFillColor(sf::Color::White);
		m_text[i].setFont(m_rm.m_font);
	}
	m_text[0].setPosition(200, 600);
	m_text[1].setPosition(750, 600);
	m_text[2].setPosition(1200, 600);

	m_text[0].setString("These hearts represent your life. \n Lose them all and its game over. \n If youre running low kill some enemies \n they might drop some.");
	m_text[1].setString("Activate this pickup to gain \n a speed boost for some time.");
	m_text[2].setString("Pick up keys to open the Boss door.");

	m_background.setPosition(0, 0);
	m_background.setTexture(&m_rm.m_menuBg);

	m_heart.setTexture(m_rm.m_heart);
	m_heart.setPosition(300, 300);

	m_star.setTexture(m_rm.m_star);
	m_star.setPosition(800, 300);

	m_key.setTexture(m_rm.m_key);
	m_key.setPosition(1200, 300);
}//!setUp

void Help::draw(sf::RenderWindow &t_window)
{
	t_window.draw(m_background);
	t_window.draw(m_titleText);
	for (int i = 0; i < 3; i++)
	{
		t_window.draw(m_text[i]);
	}
	t_window.draw(m_heart);
	t_window.draw(m_star);
	t_window.draw(m_key);
}//!draw

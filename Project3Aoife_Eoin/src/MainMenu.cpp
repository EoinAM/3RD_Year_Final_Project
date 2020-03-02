#include "MainMenu.h"


MainMenu::MainMenu(ResourceManager & t_resMan) :
	m_rm(t_resMan),
	m_musicBuffer(t_resMan.m_backgroundMusic)
{
}

MainMenu::~MainMenu()
{//!MainMenu
}

//set up the button text
void MainMenu::setUp()
{
	for (int i = 0; i < M_MAX_BUTTON; i++)
	{
		m_buttonText[i].setFont(m_rm.m_font);
		m_buttonText[i].setFillColor(sf::Color(170,170,170));
		m_buttonText[i].setCharacterSize(50);
		m_buttonText[i].setPosition(100, (i * 100) + 200);
		m_buttonText[i].setString(m_buttonString[i]);
	}//!for

	m_background.setSize(sf::Vector2f(GlobalSettings::s_width, GlobalSettings::s_height));
	m_background.setTexture(&m_rm.m_menuBg);

	//sets the first active button to the first button
	moveButton(0,1,2,3);

	m_music.setBuffer(m_musicBuffer);
	m_music.play();
	m_music.setLoop(true);
	m_music.setVolume(50);
}//!setUp

void MainMenu::render(sf::RenderWindow &t_window)
{
	t_window.draw(m_background);
	for (int i = 0; i < M_MAX_BUTTON; i++)
	{
		t_window.draw(m_buttonText[i]);
	}//!for
}//!render

void MainMenu::update(double & d_t, Xbox360Controller & t_controller)
{
	//loops the active buttons
	if (m_currentButton > 3)
	{
		m_currentButton = 0;
	}//!if
	if (m_currentButton < 0)
	{
		m_currentButton = 3;
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
		moveButton(0, 1, 2, 3);
		if (t_controller.m_currentState.A && !t_controller.m_previousState.A)
		{
			t_controller.m_currentState.A = true;
			m_switchStart = true;
		}//!if
	}//!if
	if (m_currentButton == 1)
	{
		moveButton(1, 0, 2, 3);
		if (t_controller.m_currentState.A)
		{
			m_switchHelp = true;
		}//!if
	}//!if
	if (m_currentButton == 2)
	{
		moveButton(2, 0, 1, 3);
		if (t_controller.m_currentState.A)
		{
			m_switchOptions = true;
		}//!if
	}//!if
	if (m_currentButton == 3)
	{
		moveButton(3, 0, 1, 2);
		if (t_controller.m_currentState.A)
		{
			m_switchExit = true;
		}//!if
	}//!if

}//!update


//function that changes the buttons to active or not
void MainMenu::moveButton(int t_buttonNum, int t_buttonNum2, int t_buttonNum3, int t_buttonNum4)
{
	m_buttonText[t_buttonNum].setFillColor(sf::Color::White);
	m_buttonText[t_buttonNum].setOutlineColor(sf::Color::White);
	m_buttonText[t_buttonNum].setOutlineThickness(2.5);

	m_buttonText[t_buttonNum2].setFillColor(sf::Color(170, 170, 170));
	m_buttonText[t_buttonNum2].setOutlineThickness(0);

	m_buttonText[t_buttonNum3].setFillColor(sf::Color(170, 170, 170));
	m_buttonText[t_buttonNum3].setOutlineThickness(0);

	m_buttonText[t_buttonNum4].setFillColor(sf::Color(170, 170, 170));
	m_buttonText[t_buttonNum4].setOutlineThickness(0);
}//!moveButton

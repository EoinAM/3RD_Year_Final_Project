#ifndef LEVELENDSCREEN
#define LEVELENDSCREEN

#include "Global.h"
#include "RoomBuilder.h"
#include "SFML/Graphics.hpp"
#include "Player.h"

class LevelEndScreen
{
public:
	LevelEndScreen(RoomBuilder & t_roomBuilder,ResourceManager & t_resourceMan, sf::RenderWindow & t_window, Xbox360Controller & t_control);
	~LevelEndScreen();

	void update(float t_dt, Player & t_player);
	void render();

private:

public:
	sf::View m_gameView;
	bool m_isShown{ false };
private:
	Xbox360Controller & m_controller;
	sf::RenderWindow & m_window;
	ResourceManager & m_resManager;
	RoomBuilder & m_roomBuilder;
	
	sf::Text m_levelOver_text;
};



#endif // !LEVELENDSCREEN


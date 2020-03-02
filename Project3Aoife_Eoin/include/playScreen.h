#ifndef PLAYSCREEN
#define PLAYESCREEN

#include "Global.h"
#include "LevelEndScreen.h";
#include "LoseScreen.h"
#include "Enemy.h"

class playScreen
{
public:
	playScreen(ResourceManager & t_resourceMan, sf::RenderWindow & t_window , Xbox360Controller & t_control);
	~playScreen();

	void update(double t_dt);
	void HUD();
	void render();
	void loadNewLevel(std::string t_roomName);

	void setupEnemies(double t_dt);

	void resetLevel();

private:

public:
	sf::View m_gameView;

	Xbox360Controller & m_controller;
	sf::RenderWindow & m_window;

	Player m_player;
	ResourceManager & m_resManager;

	Enemy m_enemy[4] = {Enemy(sf::Vector2f(2, 2), sf::Vector2f(2000,2000), 0.2, m_controller, m_resManager),
						Enemy(sf::Vector2f(2, 2), sf::Vector2f(2000,2000), 0.3, m_controller, m_resManager),
						Enemy(sf::Vector2f(2, 2), sf::Vector2f(2000, 2000), 0.3, m_controller, m_resManager),
						Enemy(sf::Vector2f(2, 2), sf::Vector2f(2000,2000), 0.3, m_controller, m_resManager) };

	Enemy m_bossEnemy = Enemy(sf::Vector2f(7, 7), sf::Vector2f(700, 300), 0.2, m_controller, m_resManager);
	
	RoomBuilder m_roomBuilder;

	sf::Sprite m_tutorialSprite;

	bool m_switchPause;

private:
	LevelEndScreen m_levelEndScreen;
	LoseScreen m_loseScreen;

	sf::Sprite m_livesHUD[3];
};



#endif // !PLAYSCREEN



#ifndef PICKUPS
#define PICKUPS

#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include "Xbox360Controller.h"

class PickUps
{
public:
	PickUps(ResourceManager & t_resMan, Xbox360Controller &t_control);
	~PickUps();

	void update(float & t_speed);

	void heartPosition(sf::Vector2f t_pos);
	void starPosition(sf::Vector2f t_pos);
	void keyPosition(sf::Vector2f t_pos);

	void heartCollision();
	void starCollision();
	void keyCollision();

	void setUp();

	void render(sf::RenderWindow & t_window);
	void HUDrender(sf::RenderWindow & t_window);

public:
	sf::Sprite m_star;
	sf::Sprite m_key;
	sf::Sprite m_heart;

	int m_speedTimer = 1000;
	bool m_pickedUp = false;
	bool m_keyOwned = false;

private:
	Xbox360Controller & m_controller;

	sf::Texture m_keyTexture;
	sf::Texture m_starTexture;
	sf::Texture m_heartTexture;

	bool m_heartDropped = false;
	bool m_starDropped = false;
	bool m_keyDropped = false;

	bool m_speedTimerStart = false;

	sf::Text m_lives;
	sf::Text m_pressLT;
	sf::Font m_font;

	sf::RectangleShape m_square;
};
#endif

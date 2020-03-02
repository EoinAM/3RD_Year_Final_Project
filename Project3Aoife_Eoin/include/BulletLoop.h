#ifndef BULLETLOOP
#define BULLETLOOP


#include "SFML/Graphics.hpp"
#include <array>
#include "Bullet.h"
#include "RoomBuilder.h"

class BulletLoop
{
public:
	BulletLoop() = default;
	
	void create(sf::Vector2f &t_position, sf::Vector2f &t_speed, double t_rotation, sf::Texture &t_texture);
	void update(double const &t_dt);
	void render(sf::RenderWindow &t_window);
	void setRotation(double t_angle);
	bool checkCollision(sf::RectangleShape t_body);
	bool checkCollision(sf::Sprite t_body);
	
	sf::RectangleShape returnInUse();
	void setSpeed(double speed);
	sf::Vector2f m_speed;
	bool m_poolFull{ false };
	static const int M_POOL_SIZE = 10;


private:
	
	std::array<Bullet, M_POOL_SIZE> m_bullets;
	int m_nextAvailable{ 0 };
	
};

#endif
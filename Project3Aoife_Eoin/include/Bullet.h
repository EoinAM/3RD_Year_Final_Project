#ifndef BULLET
#define BULLET


#include "SFML/Graphics.hpp"
#include "iostream"
#include "ResourceManager.h"

class Bullet
{
	friend class BulletLoop;
public:
	Bullet() {
	}
	~Bullet() {};

	void init(sf::Vector2f &t_position, double t_rotation, sf::Vector2f t_speed, sf::Texture &t_texture);
	bool update(double const & t_dt);
	bool inUse() const;
	void setRotation(double t_angle);
	void setSpeed(double speed);

private:
	double M_MAX_SPEED = 300.0;
	sf::Vector2f m_speedVector = { 0,0 };
	double m_speed{ 100.0 };
	sf::RectangleShape m_body;
	double bodyRotation;
};

#endif
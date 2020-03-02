#include "Bullet.h"

void Bullet::init(sf::Vector2f &t_position, double t_rotation, sf::Vector2f t_speed, sf::Texture &t_texture)
{
	m_body.setOrigin(m_body.getLocalBounds().width, m_body.getLocalBounds().height);
	m_body.setPosition(t_position);
	m_speed = M_MAX_SPEED;
	m_speedVector.x = t_speed.x * m_speed;
	m_speedVector.y = t_speed.y * m_speed;
	m_body.setRotation(t_rotation);
	m_body.setSize(sf::Vector2f(60, 19));
	m_body.setTexture(&t_texture);
}

bool Bullet::update(double const & t_dt)
{
	if (!inUse())
	{
		return false;
	}
	float degToRad = 3.141592653 / 180.0;
	sf::Vector2f position = m_body.getPosition();
	sf::Vector2f newPos(position.x + std::cos(degToRad * bodyRotation) * (m_speedVector.x * t_dt/15000),
		position.y + std::cos(degToRad * bodyRotation) * (m_speedVector.y * t_dt/15000));

	m_body.setPosition(newPos);
}

bool Bullet::inUse() const
{
	return m_speed == M_MAX_SPEED;
}

void Bullet::setRotation(double t_angle)
{
	m_body.setRotation(t_angle);
}

void Bullet::setSpeed(double speed)
{
	m_speed = speed;
}



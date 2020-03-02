#include "BulletLoop.h"

void BulletLoop::create(sf::Vector2f &t_position, sf::Vector2f &t_speed, double t_rotation, sf::Texture &t_texture)
{
	if (m_poolFull)
	{
		m_nextAvailable = (m_nextAvailable + 1) % M_POOL_SIZE;
	}

	m_bullets.at(m_nextAvailable).init(t_position, t_rotation, t_speed, t_texture);
	m_speed = t_speed;
	update(0);
}

void BulletLoop::update(double const & t_dt)
{
	int activeCount = 0;
	m_poolFull = false;

	for (int i = 0; i < M_POOL_SIZE; i++)
	{
		if (!m_bullets.at(i).update(t_dt))
		{
			m_nextAvailable = i;
		}
		else
		{
			activeCount++;
		}
		m_bullets.at(i).update(t_dt);
	}

	if (M_POOL_SIZE == activeCount)
	{
		m_poolFull = true;
	}
}

void BulletLoop::render(sf::RenderWindow & t_window)
{
	for (int i = 0; i < M_POOL_SIZE; i++)
	{
		// If projectile is active...
		if (m_bullets.at(i).inUse())
		{
			t_window.draw(m_bullets.at(i).m_body);
		}
	}
}

void BulletLoop::setRotation(double t_angle)
{
	for (int i = 0; i < M_POOL_SIZE; i++)
	{
		if (!m_bullets.at(i).inUse())
		{
			m_bullets.at(i).setRotation(t_angle);
		}
	}
}

bool BulletLoop::checkCollision(sf::RectangleShape t_body)
{
	for (int i = 0; i < M_POOL_SIZE; i++)
	{
		for (int i = 0; i < M_POOL_SIZE; i++)
		{
			if (m_bullets.at(i).inUse())
			{
				if (m_bullets.at(i).m_body.getGlobalBounds().intersects(t_body.getGlobalBounds()))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool BulletLoop::checkCollision(sf::Sprite t_body)
{
	for (int i = 0; i < M_POOL_SIZE; i++)
	{
		for (int i = 0; i < M_POOL_SIZE; i++)
		{
			if (m_bullets.at(i).inUse())
			{
				if (m_bullets.at(i).m_body.getGlobalBounds().intersects(t_body.getGlobalBounds()))
				{
					return true;
				}
			}
		}
	}
	return false;
}

sf::RectangleShape BulletLoop::returnInUse()
{
	for (int i = 0; i < M_POOL_SIZE; i++)
	{
		if (m_bullets.at(i).inUse())
		{
			return m_bullets.at(i).m_body;
		}
	}
}

void BulletLoop::setSpeed(double speed)
{
	for (int i = 0; i < M_POOL_SIZE; i++)
	{
		m_bullets.at(i).setSpeed(speed);
	}
}


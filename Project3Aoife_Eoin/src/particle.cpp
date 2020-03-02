#include "particle.h"

Particle::Particle()
{
}

Particle::~Particle()
{
}

void Particle::init(sf::Vector2f t_pos, sf::Vector2f & t_vel)
{
	m_pos = t_pos;
	m_size;
	m_color = sf::Color::Red;

	m_velocit = t_vel;
	m_timer = (rand() % m_maxTimer) + 1;
}

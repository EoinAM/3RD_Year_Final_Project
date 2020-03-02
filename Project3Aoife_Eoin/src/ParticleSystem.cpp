#include "ParticleSystem.h"


ParticleSystem::ParticleSystem()
{
}


ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::init(sf::Vector2f t_pos)
{
	m_position = t_pos;

	
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		sf::Vector2f vel = sf::Vector2f(rand() / double(RAND_MAX) * 4 - 2, rand() / double(RAND_MAX) * 4 - 2);
		m_particles[i].init(m_position, vel);
	}
}

void ParticleSystem::update()
{
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		if (m_particles[i].m_timer > 0)
		{
			m_particles[i].m_pos += (m_particles[i].m_velocit);
			m_particles[i].m_timer--;
		}
	}
}

void ParticleSystem::render(sf::RenderWindow & t_window)
{
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		if (m_particles[i].m_timer > 0)
		{
			m_particleShape.setPosition(m_particles[i].m_pos);
			m_particleShape.setSize(m_particles[i].m_size);
			m_particleShape.setFillColor(m_particles[i].m_color);
			t_window.draw(m_particleShape);
		}
	}
}

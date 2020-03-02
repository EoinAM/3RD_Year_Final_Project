#ifndef PARTICLESSYSTEM
#define PARTICLESSYSTEM

#include "SFML/Graphics.hpp"
#include "particle.h"

const int MAX_PARTICLES{ 200 };
class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void init(sf::Vector2f t_pos);
	void update();
	void render(sf::RenderWindow & t_window);

	Particle m_particles[MAX_PARTICLES];

private:
	sf::Vector2f m_position;

	sf::RectangleShape m_particleShape;
};

#endif // !PARTICLESSYSTEM

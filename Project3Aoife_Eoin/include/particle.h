#ifndef PARTICLE
#define PARTICLE

#include <SFML/Graphics.hpp>


class Particle
{
public:
	Particle();
	~Particle();

	void init(sf::Vector2f t_pos, sf::Vector2f &t_vel);
	int m_timer{ 0 };

	sf::Vector2f m_size{ 5,5 };
	sf::Vector2f m_velocit{ 1,1 };

	sf::Vector2f m_pos{ 0,0 };
	sf::Color m_color;
	int m_maxTimer{ 40 };
private:

};

#endif // !PARTICLE
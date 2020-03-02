#ifndef LIGHTING
#define LIGHTING

#include <SFML/Graphics.hpp>
#include "Global.h"
#include "ResourceManager.h"
#include <vector>

class Lighting
{
public:
	Lighting();

	~Lighting();
	
	void update(sf::Vector2f t_pos);
	void multiUpdate(std::vector<sf::Sprite> t_sprites, std::vector<sf::Vector2f> t_pos);

	void clear();

	void render(sf::RenderWindow & t_window);
	void setTexture(sf::Texture & t_texture);

	bool isActive{ false };

	sf::RenderTexture m_rendTexture;
	sf::Texture m_lightShine;

	sf::Sprite m_light1;

	sf::Sprite m_darkness;

	float m_lumin{ 200 };

	sf::BlendMode m_blendMode;        // alpha eq

private:
	

	
	

};

#endif

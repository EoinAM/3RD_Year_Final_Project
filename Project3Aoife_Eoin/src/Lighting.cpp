#include "Lighting.h"


Lighting::Lighting():
	m_blendMode(sf::BlendMode::Factor::Zero,
		sf::BlendMode::Factor::DstColor,          
		sf::BlendMode::Equation::Add,            
		sf::BlendMode::Factor::Zero,              
		sf::BlendMode::Factor::OneMinusSrcAlpha,  
		sf::BlendMode::Equation::Add)
{
	m_rendTexture.create(GlobalSettings::s_width, GlobalSettings::s_height);
	
	m_light1.setScale(sf::Vector2f(.5, .5));
}

Lighting::~Lighting()
{
}

void Lighting::update(sf::Vector2f t_pos)
{
	m_rendTexture.clear();
	m_rendTexture.draw(m_light1, m_blendMode);
	m_rendTexture.display();

	m_darkness.setTexture(m_rendTexture.getTexture());
	m_darkness.setColor(sf::Color(1.0f, 1.0f, 1.0f, m_lumin));

	m_light1.setPosition(sf::Vector2f (t_pos.x - (m_light1.getTextureRect().width * .15), t_pos.y - (m_light1.getTextureRect().height * .15)));
}

void Lighting::multiUpdate(std::vector<sf::Sprite> t_sprites, std::vector<sf::Vector2f> t_pos)
{
	m_rendTexture.clear();
	for (int i = 0; i < t_sprites.size(); i++)
	{
		t_sprites.at(i).setTexture(m_lightShine);
		t_sprites.at(i).setPosition(sf::Vector2f(t_pos.at(i).x - (t_sprites.at(i).getTextureRect().width * .4), t_pos.at(i).y - (t_sprites.at(i).getTextureRect().height * .4)));
		t_sprites.at(i).setScale(sf::Vector2f(1, 1));
		m_rendTexture.draw(t_sprites.at(i), m_blendMode);
		
	}
	m_rendTexture.display();

	m_darkness.setTexture(m_rendTexture.getTexture());
	m_darkness.setColor(sf::Color(5.0f, 5.0f, 5.0f, m_lumin));
}

void Lighting::clear()
{
	m_rendTexture.clear();
	m_rendTexture.display();

	m_darkness.setTexture(m_rendTexture.getTexture());
}

void Lighting::render (sf::RenderWindow & t_window)
{
	if (isActive)
	{
		t_window.draw(m_darkness);
	}
	
}

void Lighting::setTexture(sf::Texture & t_texture)
{
	m_lightShine = t_texture;
}



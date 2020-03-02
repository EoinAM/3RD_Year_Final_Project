#ifndef TILE
#define TILE

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Global.h"
#include "Lighting.h"

enum class TileType
{
	FLOOR,
	WALL,
	DOOR,
	LIGHT
};

class Tile
{
public: //functions
	Tile();

	~Tile();
	void render(sf::RenderWindow & t_window);

	void init(ResourceManager & resManager);

	void setTexture(TileType t_type, const int T_XPOS = 0, const int T_YPOS= 0);
	
	void updateTexture();

private: //functions


public: //variables
	Lighting m_light;
	std::map<std::string,sf::Texture> m_textureDict;
	int const M_SIZE{ 100};
	sf::Sprite m_bodySquare;

	bool isDoorOpen{ false };

	TileType m_type;
private: //variables 
	sf::IntRect m_textureRect;
	
	sf::Vector2f m_position{ 0,0 };
};

#endif // !TILE
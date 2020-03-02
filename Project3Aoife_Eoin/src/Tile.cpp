#include "Tile.h"

Tile::Tile()
{
	
}

Tile::~Tile()
{
}

/// <summary>
/// Initialises The Tile Object
/// </summary>
void Tile::init(ResourceManager & resManager)
{
	resManager;
	m_textureDict["floor_1"] = resManager.m_floor1;
	m_textureDict["floor_2"] = resManager.m_floor2;
	m_textureDict["wall_1"] = resManager.m_wall1;
	m_textureDict["wall_2"] = resManager.m_wall2;
	m_textureDict["door_open"] = resManager.m_door2;
	m_textureDict["door_close"] = resManager.m_door1;

	m_light.setTexture(resManager.m_lightOrb);

	m_bodySquare.setPosition(m_position);


}

void Tile::setTexture(TileType t_type, const int T_XPOS, const int T_YPOS)
{
	int randomNum;

	m_position = sf::Vector2f(M_SIZE * T_XPOS, M_SIZE * T_YPOS);
	m_bodySquare.setPosition(m_position);

	randomNum = std::rand() % 10;
	switch (t_type)
	{
	case TileType::FLOOR:
		m_type = TileType::FLOOR;
		if (randomNum == 2)
		{
			m_bodySquare.setTexture(m_textureDict["floor_2"]);
		}
		else
		{
			m_bodySquare.setTexture(m_textureDict["floor_1"]);
		}
		break;
	case TileType::WALL:
		m_type = TileType::WALL;
			m_bodySquare.setTexture(m_textureDict["wall_1"]);
		break;
	case TileType::DOOR:
		m_type = TileType::DOOR;
		if (isDoorOpen)
		{
			m_bodySquare.setTexture(m_textureDict["door_open"]);
		}
		else if(!isDoorOpen)
		{
			m_bodySquare.setTexture(m_textureDict["door_close"]);
		} // !DOOR
		break;

	case TileType::LIGHT:
		m_type = m_type = TileType::LIGHT;
		m_bodySquare.setTexture(m_textureDict["wall_2"]);
		break;
	} // !Switch

}

void Tile::updateTexture()
{
	if (isDoorOpen)
	{
		m_bodySquare.setTexture(m_textureDict["door_open"]);
	}
	else
	{
		m_bodySquare.setTexture(m_textureDict["door_close"]);
	}
}
// !setTexture

void Tile::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_bodySquare);
	if (m_light.isActive)
	{
		m_light.render(t_window);
	}
} // !render

#include "RoomBuilder.h"

RoomBuilder::RoomBuilder(sf::RenderWindow & t_window, ResourceManager & t_resourceManager, float t_totalRooms) :
	m_window(t_window),
	m_resManager(t_resourceManager),
	m_totalRooms(t_totalRooms)
{
	for (int i = 0; i < M_TOTALHEIGHT; i++)
	{
		for (int j = 0; j < M_TOTALWIDTH; j++)
		{
			m_tiles[i][j].init(m_resManager);
		} // !for j
		
	} // !for i
	m_lighting.setTexture(m_resManager.m_lightOrb);
	m_lighting.isActive = true;
}

RoomBuilder::~RoomBuilder()
{
} // !~RoomBuilder

/// <summary>
/// Function to load the room layout txt file
/// </summary>
/// <param name="t_roomName">file name</param>
void RoomBuilder::loadFile(std::string t_roomName)
{
	emptyRoom();

	std::cout << "builder" << std::endl;

	std::ifstream lvlfile;
	lvlfile.open(t_roomName);
	if (lvlfile.is_open())
	{
		while (!lvlfile.eof())
		{

			for (int i = 0; i < M_TOTALHEIGHT; i++)
			{

				for (int j = 0; j < M_TOTALWIDTH; j++)
				{
					lvlfile >> m_tileValue[i][j];

					if (m_tileValue[i][j] == 3)
					{
						sf::Sprite sprite;
						m_lightSprites.push_back(sprite);
						m_lightPos.push_back(sf::Vector2f(j * m_tiles[i][j].M_SIZE, i * m_tiles[i][j].M_SIZE));
					}

					m_tiles[i][j].setTexture(TileType(m_tileValue[i][j]), j, i);
					if (j == M_TOTALWIDTH - 1)
					{
						std::cout << std::endl;
					} //! if

				} // for j

			} // !for i

		} // !while loop
		lvlfile.close();
	} // !if(lvl.is_open) 
	m_lighting.multiUpdate(m_lightSprites, m_lightPos);
	render();

}

/// <summary>
/// Function to empty game room
/// </summary>
void RoomBuilder::emptyRoom()
{
	for (int i = 0; i < M_TOTALHEIGHT; i++)
	{
		for (int j = 0; j < M_TOTALWIDTH; j++)
		{
			m_tileValue[i][j] = 0;
		} // !for j

	} // !for i


	m_lightPos.clear();
	m_lightSprites.clear();
	m_lighting.clear();
} // !emptyRoom



void RoomBuilder::render()
{
	for (int i = 0; i < M_TOTALHEIGHT; i++)
	{
		for (int j = 0; j < M_TOTALWIDTH; j++)
		{
			m_tiles[i][j].render(m_window);
		} // !for j

	} // !for i
	m_lighting.render(m_window);
} // !render

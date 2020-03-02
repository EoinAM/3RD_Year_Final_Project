#ifndef ROOMBUILDER
#define ROOMBUILDER

#include "ResourceManager.h"
#include "Tile.h"
#include <fstream>

class RoomBuilder
{
public: // functions
	RoomBuilder(sf::RenderWindow & t_window, ResourceManager & t_resourceManager, float t_totalRooms = 0);
	~RoomBuilder();
	
	void loadFile(std::string t_roomName);

	void render();

private: // functions
	void emptyRoom();

	

public: // variables

	static const int M_TOTALHEIGHT = 9;
	static const int M_TOTALWIDTH = 16;
	Tile m_tiles[M_TOTALHEIGHT][M_TOTALWIDTH];
	int m_roomIndex = 0;
	int m_totalRooms = 0;
	Lighting m_lighting;

private: //variables
	const int MAX_TEXTURES{ 6 };
	int m_tileValue[M_TOTALHEIGHT][M_TOTALWIDTH];
	
	std::vector<sf::Texture> m_textures;

	std::vector<sf::Sprite> m_lightSprites;
	std::vector<sf::Vector2f> m_lightPos;

	

	sf::RenderWindow & m_window;

	ResourceManager & m_resManager;

};

#endif // !ROOMBUILDER

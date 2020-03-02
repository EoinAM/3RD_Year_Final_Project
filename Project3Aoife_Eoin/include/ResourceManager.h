#ifndef RESOURCEMANAGER
#define RESOURCEMANAGER

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ResourceManager
{
public: //functions
	ResourceManager();
	~ResourceManager();

	void loadAssets();

public: //variables
	static const int NOOFROOMTEXTURES{ 6 };

	//Fonts
	sf::Font m_font;
	
	//Tiles
	sf::Texture m_floor1;
	sf::Texture m_floor2;
	sf::Texture m_wall1;
	sf::Texture m_wall2;
	sf::Texture m_door1;
	sf::Texture m_door2;

	sf::Texture m_walkRight;
	sf::Texture m_walkLeft;
	sf::Texture m_walkUp;
	sf::Texture m_walkDown;

	sf::Texture m_walkIdleRight;
	sf::Texture m_walkIdleLeft;
	sf::Texture m_walkIdleUp;
	sf::Texture m_walkIdleDown;

	sf::Texture m_spiderWalkRight;
	sf::Texture m_spiderWalkLeft;
	sf::Texture m_spiderWalkUp;
	sf::Texture m_spiderWalkDown;

	sf::Texture m_spiderIdleRight;
	sf::Texture m_spiderIdleLeft;
	sf::Texture m_spiderIdleUp;
	sf::Texture m_spiderIdleDown;

	sf::Texture m_bullet;
	sf::Texture m_spiderWeb;

	sf::Texture m_tutorial1;

	sf::SoundBuffer m_backgroundMusic;
	sf::SoundBuffer m_walkingSound;
	sf::SoundBuffer m_playerBuffer;
	sf::SoundBuffer m_knifeBuffer;
	sf::SoundBuffer m_spiderBuffer;

	// Main Menu
	sf::Texture m_menuBg;

	sf::Texture m_heart;
	sf::Texture m_halfHeart;
	sf::Texture m_emptyHeart;

	sf::Texture m_key;
	sf::Texture m_star;

	sf::Texture m_lightOrb;



};


#endif // !RESOURCEMANAGER



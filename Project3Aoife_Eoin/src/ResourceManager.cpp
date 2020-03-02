#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	loadAssets();
}


ResourceManager::~ResourceManager()
{
}

void ResourceManager::loadAssets()
{
	//Fonts
	m_font.loadFromFile("Assets\\Font\\test.ttf");

	//Tiles
	m_floor1.loadFromFile("Assets\\Sprites\\Floor1.png");
	m_floor2.loadFromFile("Assets\\Sprites\\Floor2.png");
	m_wall1.loadFromFile("Assets\\Sprites\\Wall1.png");
	m_wall2.loadFromFile("Assets\\Sprites\\wall2.png");
	m_door1.loadFromFile("Assets\\Sprites\\DoorClosed.png");
	m_door2.loadFromFile("Assets\\Sprites\\DoorOpen.png");

	//Animation
	m_walkRight.loadFromFile("Assets\\Sprites\\Walk\\WalkRightSpriteSheet.png");
	m_walkLeft.loadFromFile("Assets\\Sprites\\Walk\\WalkLeftSpriteSheet.png");
	m_walkUp.loadFromFile("Assets\\Sprites\\Walk\\WalkUpSpriteSheet.png");
	m_walkDown.loadFromFile("Assets\\Sprites\\Walk\\WalkDownSpriteSheet.png");

	//enemy animation (spider)
	m_spiderWalkRight.loadFromFile("Assets\\Sprites\\Spider\\rightSpider.png");
	m_spiderWalkLeft.loadFromFile("Assets\\Sprites\\Spider\\leftSpider.png");
	m_spiderWalkUp.loadFromFile("Assets\\Sprites\\Spider\\upSpider.png");
	m_spiderWalkDown.loadFromFile("Assets\\Sprites\\Spider\\downSpider.png");

	//Sprites
	m_bullet.loadFromFile("Assets\\Sprites\\knife.png");
	m_spiderWeb.loadFromFile("Assets\\Sprites\\spiderWeb.png");

	m_menuBg.loadFromFile("Assets\\Sprites\\menuTexture.png");

	m_tutorial1.loadFromFile("Assets\\Sprites\\Tutorial\\tutorial1.png");

	//Sound
	m_backgroundMusic.loadFromFile("Assets\\Sounds\\Music1.ogg");
	m_walkingSound.loadFromFile("Assets\\Sounds\\spiderWalk.ogg");
	m_playerBuffer.loadFromFile("Assets\\Sounds\\playerHit.ogg");
	m_knifeBuffer.loadFromFile("Assets\\Sounds\\Knife.ogg");
	m_spiderBuffer.loadFromFile("Assets\\Sounds\\spiderHit.wav");

	m_heart.loadFromFile("Assets\\Sprites\\HUD\\heart.png");
	m_halfHeart.loadFromFile("Assets\\Sprites\\HUD\\halfHeart.png");
	m_emptyHeart.loadFromFile("Assets\\Sprites\\HUD\\emptyHeart.png");

	m_key.loadFromFile("Assets\\Sprites\\PickUps\\key.png");
	m_star.loadFromFile("Assets\\Sprites\\PickUps\\star.png");

	m_lightOrb.loadFromFile("Assets\\Sprites\\light.png");

}

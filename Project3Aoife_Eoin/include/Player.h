#ifndef PLAYER
#define PLAYER


#include "Xbox360Controller.h"
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "RoomBuilder.h"
#include "BulletLoop.h"
#include "Animation.h"
#include "ResourceManager.h"
#include "Collision.h"
#include "PickUps.h"
#include "Lighting.h"
#include "ParticleSystem.h"

enum PlayerState
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	IDLERIGHT,
	IDLELEFT,
	IDLEUP,
	IDLEDOWN
};

class Player
{
public: //functions
	Player(sf::Vector2f t_size, sf::Vector2f t_pos, Xbox360Controller &t_control, ResourceManager & t_resMan);
	~Player();

	void update(double const & t_dt, RoomBuilder & t_room);

	void movePlayer( double t_dt);
	void render(sf::RenderWindow & t_window);

	void animationHandler();
	
	void checkTileCollision(RoomBuilder & t_room, sf::RectangleShape t_body, bool t_bossAlive);
	void checkTileCollisionWithBullet(RoomBuilder & t_room);
	void checkEnemyCollisionWithBullet(sf::RectangleShape &t_enemy, bool &t_alive);
	void checkEnemyCollisionWithPlayer(sf::RectangleShape t_enemy);
	void checkBossCollisionWithBullet(sf::RectangleShape &t_enemy, bool &t_alive);

	void checkPickUpStarCollision(sf::Sprite t_pickup);
	void checkPickUpHeartCollision(sf::Sprite t_pickup);
	void checkPickUpKeyCollision(sf::Sprite t_pickup);

	void fire();
	void playerShooting(double const & t_dt);

	void reset();

private: //functions

	float m_speed{ 2 };

	sf::Texture &m_bulletTexture;

	PickUps m_pickUps;

	ResourceManager & m_resourceManager;

	Animation m_walkRightAnimation;
	Animation m_walkLeftAnimation;
	Animation m_walkUpAnimation;
	Animation m_walkDownAnimation;

	Animation m_idleRightAnimation;
	Animation m_idleLeftAnimation;
	Animation m_idleUpAnimation;
	Animation m_idleDownAnimation;

public: // variables

	sf::Vector2f m_bulletSpeed{ 0.5,0.5 };
	sf::Vector2f m_position{ 0,0 };
	int currentRoom = 1;

	bool m_levelEnd{ false };
	sf::RectangleShape m_body;
	BulletLoop m_pool;
	float m_lives = 3;
	bool m_alive = true;
	bool m_pickUpDropped = false;
	bool resetEnemies = false;
	int bossHealth = 20;
	ParticleSystem m_particleSystem;
	sf::Sound m_hitSound;


private: //variables
	sf::SoundBuffer & m_sBuffer;
	sf::SoundBuffer & m_knifeBuffer;
	sf::SoundBuffer & m_enemyHit;

	sf::Sound m_enemyHitSound;
	sf::Sound m_knifeSound;

	sf::Vector2f m_prevPos{ 0,0 };
	PlayerState m_currentState;
	PlayerState m_previousState;
	double m_waitTime = 1500;
	double m_time = 0;
	bool m_requestFire = false;
	int collisionTimer = 0;
	double m_angle;
	int randomNum;
	Xbox360Controller & m_control;
};


#endif // !PLAYER


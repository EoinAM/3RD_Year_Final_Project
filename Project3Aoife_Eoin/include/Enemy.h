#ifndef ENEMY
#define ENEMY

#include "Xbox360Controller.h"
#include "SFML/Graphics.hpp"
#include "RoomBuilder.h"
#include "Animation.h"
#include "ResourceManager.h"
#include "BulletLoop.h"
#include "Collision.h"

enum EnemyState
{
	ELEFT,
	ERIGHT,
	EUP,
	EDOWN,
	EIDLERIGHT,
	EIDLELEFT,
	EIDLEUP,
	EIDLEDOWN
};

class Enemy
{
public:
	Enemy(sf::Vector2f t_size, sf::Vector2f t_pos, float t_speed, Xbox360Controller &t_control, ResourceManager & t_resManager);
	~Enemy();

	void updateEnemyFollow(double const & t_dt, RoomBuilder & t_room, sf::Vector2f t_playerPos);
	void updateEnemyFollowShoot(double const & t_dt, RoomBuilder & t_room, sf::Vector2f t_playerPos);
	void updateEnemyShoot(double const & t_dt, RoomBuilder & t_room, sf::Vector2f t_playerPos);
	void updateBoss(double const & t_dt, RoomBuilder & t_room, sf::Vector2f t_playerPos);

	void moveEnemy(sf::Vector2f t_playerPos, double t_dt);
	void render(sf::RenderWindow & t_window);

	void animationHandler();

	void checkEnemyTileCollision(RoomBuilder & t_room);
	void checkPlayerCollisionWithBullet(sf::RectangleShape & t_player, float &t_lives, sf::Sound & t_playerHit);
	void checkTileCollisionWithBullet(RoomBuilder & t_room);

	void fire();
	void enemyShooting(double const & t_dt);
	void bossFire();
	void bossShooting(double const & t_dt);

	void bossHealth(int &t_health);
	void reset();
private:
	sf::Texture &m_bulletTexture;
	ResourceManager & m_resourceManager;

	Animation m_walkRightAnimation;
	Animation m_walkLeftAnimation;
	Animation m_walkUpAnimation;
	Animation m_walkDownAnimation;

	Animation m_idleRightAnimation;
	Animation m_idleLeftAnimation;
	Animation m_idleUpAnimation;
	Animation m_idleDownAnimation;

private:
	float m_speed{ 0 };
	Xbox360Controller & m_control;
	sf::Vector2f m_movement{ 0,0 };
	

	EnemyState m_currentState;
	EnemyState m_previousState;

	double m_waitTime = 3000;
	double m_time = 0;
	float m_angle = 0;
	bool m_requestFire = false;
public:
	sf::Vector2f m_prevPosition{ 0,0 };
	sf::Vector2f m_position{ 0,0 };
	sf::Vector2f m_bulletSpeed{ 0.3,0.3 };
	sf::Vector2f m_bossBulletSpeed[8] = { sf::Vector2f {0,1}, sf::Vector2f {1,1} ,sf::Vector2f {1,0} ,sf::Vector2f {-1,-1} ,sf::Vector2f {0,-1} ,sf::Vector2f {-1,0} ,sf::Vector2f {1,1} ,sf::Vector2f {1,1} };
	BulletLoop m_enemyPool;
	BulletLoop m_bossPool[8];
	int currentRoom = 1;
	sf::RectangleShape m_body;
	bool m_alive = true;
	bool dontMove = false;
	sf::RectangleShape m_bossHealthBar;
};
#endif
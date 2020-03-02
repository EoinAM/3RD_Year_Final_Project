#include "Enemy.h"

Enemy::Enemy(sf::Vector2f t_size, sf::Vector2f t_pos, float t_speed, Xbox360Controller & t_control, ResourceManager & t_resManager):
	m_resourceManager(t_resManager),
	m_position(t_pos),
	m_control(t_control),
	m_walkRightAnimation(m_body, 3, t_resManager.m_spiderWalkRight, sf::IntRect(0, 0, 52, 48)),
	m_walkLeftAnimation(m_body, 3, t_resManager.m_spiderWalkLeft, sf::IntRect(0, 0, 52, 48)),
	m_walkUpAnimation(m_body, 3, t_resManager.m_spiderWalkUp, sf::IntRect(0, 0, 52, 48)),
	m_walkDownAnimation(m_body, 3, t_resManager.m_spiderWalkDown, sf::IntRect(0, 0, 52, 48)),
	m_idleRightAnimation(m_body, 1, t_resManager.m_spiderWalkRight, sf::IntRect(0, 0, 52, 48)),
	m_idleLeftAnimation(m_body, 1, t_resManager.m_spiderWalkLeft, sf::IntRect(0, 0, 52, 48)),
	m_idleUpAnimation(m_body, 1, t_resManager.m_spiderWalkUp, sf::IntRect(0, 0, 52, 48)),
	m_idleDownAnimation(m_body, 1, t_resManager.m_spiderWalkDown, sf::IntRect(0, 0, 52, 48)),
	m_currentState{ EnemyState::ERIGHT },
	m_speed{ t_speed },
	m_bulletTexture(m_resourceManager.m_spiderWeb)
{
	m_body.setPosition(t_pos);
	m_body.setSize(sf::Vector2f(52, 48));
	m_body.setScale(t_size);
	m_body.setTexture(&m_resourceManager.m_walkUp);
	m_body.setTextureRect(sf::IntRect(0, 0, 54, 54));

	sf::Vector2f zero = sf::Vector2f(0, 0);
	for (int i = 0; i < m_enemyPool.M_POOL_SIZE; i++)
	{
		m_enemyPool.create(zero, zero, 0, m_resourceManager.m_spiderWeb);
	}
	

}

Enemy::~Enemy()
{
}

void Enemy::updateEnemyFollow(double const & t_dt, RoomBuilder & t_room, sf::Vector2f t_playerPos)
{
	if (m_alive)
	{
		animationHandler();
		m_prevPosition = m_position;
		moveEnemy(t_playerPos, t_dt);
		m_body.setPosition(m_position.x + m_movement.x, m_position.y + m_movement.y);
	}
	else
	{
		m_body.setPosition(1000, 1000);
	}
}

void Enemy::updateEnemyFollowShoot(double const & t_dt, RoomBuilder & t_room, sf::Vector2f t_playerPos)
{
	animationHandler();
	m_prevPosition = m_body.getPosition();

	if (m_time > 0)
	{
		m_time--;
	}//!if
	if (m_time == 0)
	{
		m_requestFire = false;
	}//!if
	enemyShooting(t_dt);

	if (m_alive)
	{
		moveEnemy(t_playerPos, t_dt);
		m_body.setPosition(m_body.getPosition().x + m_movement.x, m_body.getPosition().y + m_movement.y);
	}
	else
	{
		m_position = sf::Vector2f{ 1000, 1000 };
		m_body.setPosition(m_position);
	}

	//checks which way the enemy is facing and changes the direction 
	//the bullet will move accoringly
	switch (m_currentState)
	{
	case ERIGHT:
		m_bulletSpeed = { 1, 0 };
		break;
	case ELEFT:
		m_bulletSpeed = { -1, 0 };
		break;
	case EUP:
		m_bulletSpeed = { 0, -1 };
		break;
	case EDOWN:
		m_bulletSpeed = { 0, 1 };
		break;
	case EIDLERIGHT:
		m_bulletSpeed = { 1, 0 };
		break;
	case EIDLELEFT:
		m_bulletSpeed = { -1, 0 };
		break;
	case EIDLEUP:
		m_bulletSpeed = { 0, -1 };
		break;
	case EIDLEDOWN:
		m_bulletSpeed = { 0, 1 };
		break;
	default:
		break;
	}
}

void Enemy::updateEnemyShoot(double const & t_dt, RoomBuilder & t_room, sf::Vector2f t_playerPos)
{
	animationHandler();

	if (m_time > 0)
	{
		m_time--;
	}//!if
	if (m_time == 0)
	{
		m_requestFire = false;
	}//!if
	enemyShooting(t_dt);
	if (!m_alive)
	{
		m_body.setPosition(1000, 1000);
	}


	moveEnemy(t_playerPos, t_dt);
	m_body.setPosition(m_body.getPosition().x, m_body.getPosition().y);

	//checks which way the enemy is facing and changes the direction 
	//the bullet will move accoringly
	switch (m_currentState)
	{
	case EIDLERIGHT:
		m_bulletSpeed = { 1, 0 };
		break;
	case EIDLELEFT:
		m_bulletSpeed = { -1, 0 };
		break;
	case EIDLEUP:
		m_bulletSpeed = { 0, -1 };
		break;
	case EIDLEDOWN:
		m_bulletSpeed = { 0, 1 };
		break;
	default:
		break;
	}
}

void Enemy::updateBoss(double const & t_dt, RoomBuilder & t_room, sf::Vector2f t_playerPos)
{
	animationHandler();
	m_prevPosition = m_body.getPosition();

	if (m_time > 0)
	{
		m_time--;
	}//!if
	if (m_time == 0)
	{
		m_requestFire = false;
	}//!if
	bossShooting(t_dt);

	if (m_alive)
	{
		moveEnemy(t_playerPos, t_dt);
		m_body.setPosition(m_body.getPosition().x + m_movement.x, m_body.getPosition().y + m_movement.y);
	}
	else
	{
		m_position = sf::Vector2f{ 1000, 1000 };
		m_body.setPosition(m_position);
	}

	m_bossBulletSpeed[0] = { 0, 0.5 };
	m_bossBulletSpeed[1] = { 0.5, 0.5 };
	m_bossBulletSpeed[2] = { 0.5, 0 };
	m_bossBulletSpeed[3] = { 0.5, -0.5 };
	m_bossBulletSpeed[4] = { 0, -0.5 };
	m_bossBulletSpeed[5] = { -0.5, -0.5 };
	m_bossBulletSpeed[6] = { -0.5, 0 };
	m_bossBulletSpeed[7] = { -0.5, 0.5 };

}

void Enemy::moveEnemy(sf::Vector2f t_playerPos, double t_dt)
{
	m_prevPosition = m_body.getPosition();

	sf::Vector2f direction;

	direction.x = t_playerPos.x -m_body.getPosition().x - 100;
	direction.y = t_playerPos.y -m_body.getPosition().y - 100;

	//if the enemy isnt stationary then this bool should be false 
	if (dontMove == false)
	{
		if (direction.x < -0.5)
		{
			m_movement.x = -(m_speed / t_dt);
			m_angle = -180;
			m_currentState = EnemyState::ELEFT;
		}
		else if (direction.x > 0.5)
		{
			m_movement.x = (m_speed / t_dt);
			m_angle = 0;
			m_currentState = EnemyState::ERIGHT;
		}
		else
		{
			m_movement.x = 0;
		}

		if (direction.y < -0.5)
		{
			m_movement.y = -(m_speed / t_dt);
			m_angle = -90;
			m_currentState = EnemyState::EUP;
		}
		else if (direction.y > 0.5)
		{
			m_movement.y = (m_speed / t_dt);
			m_angle = 90;
			m_currentState = EnemyState::EDOWN;
		}
		else
		{
			m_movement.y = 0;
		}
	}
	//if the enemy is a stationary enemy then this bool should be true
	if (dontMove)
	{
		if (direction.x < -0.5)
		{
			m_angle = -180;
			m_currentState = EnemyState::EIDLELEFT;
		}
		else if (direction.x > 0.5)
		{
			m_angle = 0;
			m_currentState = EnemyState::EIDLERIGHT;
		}

		if (direction.y < -100)
		{
			m_angle = -90;
			m_currentState = EnemyState::EIDLEUP;
		}
		else if (direction.y > 100)
		{
			m_angle = 90;
			m_currentState = EnemyState::EIDLEDOWN;
		}
	}
}


void Enemy::render(sf::RenderWindow & t_window)
{
	if (m_alive == true)
	{
	t_window.draw(m_body);
	m_enemyPool.render(t_window);
	
		for (int i = 0; i < 8; i++)
		{
			m_bossPool[i].render(t_window);
		}
		t_window.draw(m_bossHealthBar);
	}
}

void Enemy::animationHandler()
{
	switch (m_currentState)
	{
	case ERIGHT:
		m_body.setTexture(&m_resourceManager.m_spiderWalkRight);
		m_walkRightAnimation.update();
		break;
	case ELEFT:
		m_body.setTexture(&m_resourceManager.m_spiderWalkLeft);
		m_walkLeftAnimation.update();
		break;
	case EUP:
		m_body.setTexture(&m_resourceManager.m_spiderWalkUp);
		m_walkUpAnimation.update();
		break;
	case EDOWN:
		m_body.setTexture(&m_resourceManager.m_spiderWalkDown);
		m_walkDownAnimation.update();
		break;
	case EIDLERIGHT:
		m_idleRightAnimation.update();
		break;
	case EIDLELEFT:
		m_idleLeftAnimation.update();
		break;
	case EIDLEUP:
		m_idleUpAnimation.update();
		break;
	case EIDLEDOWN:
		m_idleDownAnimation.update();
		break;
	default:
		break;
	}
}

void Enemy::checkEnemyTileCollision(RoomBuilder & t_room)
{
	for (int i = 0; i < t_room.M_TOTALHEIGHT; i++)
	{
		for (int j = 0; j < t_room.M_TOTALWIDTH; j++)
		{
			
			if (m_body.getGlobalBounds().intersects(t_room.m_tiles[i][j].m_bodySquare.getGlobalBounds()))
			{
				if (t_room.m_tiles[i][j].m_type == TileType::WALL)
				{
					m_body.setPosition(m_prevPosition);
				}// !if
			}// !if
		}// !for
	}// !for
}

//checks if the player collided with the enemys bullet
void Enemy::checkPlayerCollisionWithBullet(sf::RectangleShape & t_player, float &t_lives, sf::Sound & t_playerHit)
{
	for (int i = 0; i < 8; i++)
	{
		if (m_bossPool[i].m_speed != sf::Vector2f(0, 0))
		{
			if (m_bossPool[i].checkCollision(t_player))
			{
				m_bossPool[i].setSpeed(0.0);
				t_playerHit.play();
				t_lives -= 0.5;
			}
		}
	}
	if (m_enemyPool.m_speed != sf::Vector2f(0, 0))
	{
		if (m_enemyPool.checkCollision(t_player))
		{
			m_enemyPool.setSpeed(0.0);
			t_playerHit.play();
			t_lives -= 0.5;
		}//!if
	}
}

void Enemy::checkTileCollisionWithBullet(RoomBuilder & t_room)
{
	for (int i = 0; i < t_room.M_TOTALHEIGHT; i++)
	{
		for (int j = 0; j < t_room.M_TOTALWIDTH; j++)
		{
			for (int boss = 0; boss < 8; boss++)
			{
				if (m_bossPool[boss].m_speed != sf::Vector2f(0, 0))
				{
					if (m_bossPool[boss].checkCollision(t_room.m_tiles[i][j].m_bodySquare) && t_room.m_tiles[i][j].m_type == TileType::WALL)
					{
							m_bossPool[boss].setSpeed(0.0);
					}
				}
			}
			if (m_enemyPool.m_speed != sf::Vector2f(0, 0))
			{
				if (m_enemyPool.checkCollision(t_room.m_tiles[i][j].m_bodySquare) && t_room.m_tiles[i][j].m_type == TileType::WALL)
				{
					if (t_room.m_tiles[i][j].m_type == TileType::WALL)
					{
						m_enemyPool.setSpeed(0.0);
					}
				}// !if
			}
		}
	}// !for
}

//creates the bullet
//gets the position the bullet will fire
void Enemy::fire()
{
	if (m_body.getScale().x > 0)
	{
		sf::Vector2f firePosition(m_body.getPosition().x + m_body.getLocalBounds().width, m_body.getPosition().y + m_body.getLocalBounds().height + 30);
		m_enemyPool.create(firePosition, m_bulletSpeed, m_angle, m_resourceManager.m_spiderWeb);
	}//!if

}

//when the enemy should fire
//updates the bullets
void Enemy::enemyShooting(double const & t_dt)
{
	if (!m_requestFire)
	{
		m_time = m_waitTime;
		m_requestFire = true;
		fire();
	}//!if
	m_enemyPool.update(t_dt);
}

//creates the bullet
//gets the position the bullet will fire
void Enemy::bossFire()
{
	if (m_body.getScale().x > 0)
	{
		sf::Vector2f firePosition(m_body.getPosition().x + m_body.getLocalBounds().width + 200, m_body.getPosition().y + m_body.getLocalBounds().height + 100);
		m_bossPool[0].create(firePosition, m_bossBulletSpeed[0], 90, m_resourceManager.m_spiderWeb);
		m_bossPool[1].create(firePosition, m_bossBulletSpeed[1], 45, m_resourceManager.m_spiderWeb);
		m_bossPool[2].create(firePosition, m_bossBulletSpeed[2], 0, m_resourceManager.m_spiderWeb);
		m_bossPool[3].create(firePosition, m_bossBulletSpeed[3], 315, m_resourceManager.m_spiderWeb);
		m_bossPool[4].create(firePosition, m_bossBulletSpeed[4], 270, m_resourceManager.m_spiderWeb);
		m_bossPool[5].create(firePosition, m_bossBulletSpeed[5], 225, m_resourceManager.m_spiderWeb);
		m_bossPool[6].create(firePosition, m_bossBulletSpeed[6], 180, m_resourceManager.m_spiderWeb);
		m_bossPool[7].create(firePosition, m_bossBulletSpeed[7], 135, m_resourceManager.m_spiderWeb);
	}//!if

}

void Enemy::bossShooting(double const & t_dt)
{
	if (!m_requestFire)
	{
		m_time = m_waitTime;
		m_requestFire = true;
		bossFire();
	}//!if

	for (int i = 0; i < 8; i++)
	{
		m_bossPool[i].update(t_dt);
	}
}

void Enemy::bossHealth(int & t_health)
{
	m_bossHealthBar.setFillColor(sf::Color::Red);
	m_bossHealthBar.setOutlineColor(sf::Color(61, 61, 61));
	m_bossHealthBar.setPosition(400, -80);
	m_bossHealthBar.setSize(sf::Vector2f(t_health * 10, 50));
}

void Enemy::reset()
{
	m_speed = 0;
	m_time = 0;
	m_angle = 0;
	m_requestFire = false;
	m_position = sf::Vector2f(0, 0);
	m_prevPosition = m_position;
	currentRoom = 1;
	m_alive = true;
}

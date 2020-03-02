#include "Player.h"

Player::Player(sf::Vector2f t_size, sf::Vector2f t_pos, Xbox360Controller & t_control, ResourceManager & t_resMan) :
	m_resourceManager(t_resMan),
	m_position(t_pos),
	m_walkRightAnimation(m_body, 3, t_resMan.m_walkRight, sf::IntRect(0, 0, 30, 35)),
	m_walkLeftAnimation(m_body, 3, t_resMan.m_walkLeft, sf::IntRect(0, 0, 30, 35)),
	m_walkUpAnimation(m_body, 3, t_resMan.m_walkUp, sf::IntRect(0, 0, 30, 35)),
	m_walkDownAnimation(m_body, 3, t_resMan.m_walkDown, sf::IntRect(0, 0, 30, 35)),
	m_idleRightAnimation(m_body, 1, t_resMan.m_walkRight, sf::IntRect(0, 0, 29, 34)),
	m_idleLeftAnimation(m_body, 1, t_resMan.m_walkLeft, sf::IntRect(0, 0, 29, 34)),
	m_idleUpAnimation(m_body, 1, t_resMan.m_walkUp, sf::IntRect(0, 0, 29, 34)),
	m_idleDownAnimation(m_body, 1, t_resMan.m_walkDown, sf::IntRect(0, 0, 29, 34)),
	m_currentState{ PlayerState::RIGHT },
	m_control(t_control),
	m_bulletTexture(t_resMan.m_bullet),
	m_pickUps(t_resMan, t_control),
	m_sBuffer(t_resMan.m_playerBuffer),
	m_knifeBuffer(t_resMan.m_knifeBuffer),
	m_enemyHit(t_resMan.m_spiderBuffer)
{
	m_body.setPosition(t_pos);
	m_body.setRotation(0);
	m_body.setSize(sf::Vector2f(30,35));
	m_body.setScale(2, 2);
	m_body.setTexture(&m_resourceManager.m_walkUp);
	m_body.setTextureRect(sf::IntRect(0, 0, 30, 35));

	m_hitSound.setBuffer(m_sBuffer);
	m_hitSound.setLoop(false);
	m_hitSound.setVolume(20);

	m_enemyHitSound.setBuffer(m_enemyHit);
	m_enemyHitSound.setLoop(false);
	m_enemyHitSound.setVolume(20);
	
	m_knifeSound.setBuffer(m_knifeBuffer);
	m_knifeSound.setLoop(false);
	m_knifeSound.setVolume(60);
	sf::Vector2f zero = sf::Vector2f(-200, -200);
	for (int i = 0; i < m_pool.M_POOL_SIZE; i++)
	{
		m_pool.create(zero, zero, 0, m_resourceManager.m_bullet);
	}

	
}
Player::~Player()
{
}// !~Player

void Player::update(double const & t_dt, RoomBuilder & t_room)
{
	animationHandler();
	m_prevPos = m_position;

	if (m_time > 0)
	{
		m_time--;
	}//!if
	if (m_time == 0)
	{
		m_requestFire = false;
	}//!if
	movePlayer(t_dt);
	playerShooting(t_dt);

	if (m_lives <= 0)
	{
		m_alive = false;
	}
	if (m_lives > 3)
	{
		m_lives = 3;
	}

	checkPickUpStarCollision(m_pickUps.m_star);
	checkPickUpHeartCollision(m_pickUps.m_heart);
	checkPickUpKeyCollision(m_pickUps.m_key);

	m_pickUps.update(m_speed);
	m_particleSystem.update();
}//!update

void Player::movePlayer(double t_dt)
{
	//walk right
	if (m_control.m_currentState.LeftThumbStick.x > Xbox360Controller::m_analogThreshold)
	{
		m_position.x += (m_speed / t_dt);
		m_angle = 0;
		m_currentState = PlayerState::RIGHT;
	}//!if
	else
	{
		if (m_previousState == PlayerState::RIGHT)
		{
			m_currentState = PlayerState::IDLERIGHT;
		}
	}

	if (m_control.m_currentState.LeftThumbStick.x < -Xbox360Controller::m_analogThreshold)
	{
		m_position.x -= (m_speed / t_dt);
		m_angle = -180;
		m_currentState = PlayerState::LEFT;
	}//!if
	else
	{
		if (m_previousState == PlayerState::LEFT)
		{
			m_currentState = PlayerState::IDLELEFT;
		}
	}
	//walk down
	if (m_control.m_currentState.LeftThumbStick.y > Xbox360Controller::m_analogThreshold)
	{
		m_position.y += (m_speed / t_dt);
		m_angle = 90;
		m_currentState = PlayerState::DOWN;
	}//!if
	else
	{
		if (m_previousState == PlayerState::DOWN)
		{
			m_currentState = PlayerState::IDLEDOWN;
		}
	}

	//walk up
	if (m_control.m_currentState.LeftThumbStick.y < -Xbox360Controller::m_analogThreshold)
	{
		m_position.y -= (m_speed / t_dt);
		m_angle = -90;
		m_currentState = PlayerState::UP;
	}//!if
	else
	{
		if (m_previousState == PlayerState::UP)
		{
			m_currentState = PlayerState::IDLEUP;
		}
	}
	m_body.setPosition(m_position);
	m_previousState = m_currentState;

	if (m_control.m_currentState.RTrigger > 1)
	{
		switch (m_currentState)
		{
		case RIGHT:
			m_bulletSpeed = { 1, 0 };
			break;
		case LEFT:
			m_bulletSpeed = { -1, 0 };
			break;
		case UP:
			m_bulletSpeed = { 0, -1 };
			break;
		case DOWN:
			m_bulletSpeed = { 0, 1 };
			break;
		case IDLERIGHT:
			m_bulletSpeed = { 1, 0 };
			break;
		case IDLELEFT:
			m_bulletSpeed = { -1, 0 };
			break;
		case IDLEUP:
			m_bulletSpeed = { 0, -1 };
			break;
		case IDLEDOWN:
			m_bulletSpeed = { 0, 1 };
			break;
		default:
			break;
		}
	}//!if
}// !movePlayer



void Player::animationHandler()
{
	switch (m_currentState)
	{
	case RIGHT:
		m_body.setTexture(&m_resourceManager.m_walkRight);
		m_walkRightAnimation.update();
		break;
	case LEFT:
		m_body.setTexture(&m_resourceManager.m_walkLeft);
		m_walkLeftAnimation.update();
		break;
	case UP:
		m_body.setTexture(&m_resourceManager.m_walkUp);
		m_walkUpAnimation.update();
		break;
	case DOWN:
		m_body.setTexture(&m_resourceManager.m_walkDown);
		m_walkDownAnimation.update();
		break;
	case IDLERIGHT:
		m_idleRightAnimation.update();
		break;
	case IDLELEFT:
		m_idleLeftAnimation.update();
		break;
	case IDLEUP:
		m_idleUpAnimation.update();
		break;
	case IDLEDOWN:
		m_idleDownAnimation.update();
		break;
	default:
		break;

	}//!switch
}

void Player::checkTileCollision(RoomBuilder & t_room, sf::RectangleShape t_body , bool t_bossAlive)
{
	for (int i = 0; i < t_room.M_TOTALHEIGHT; i++)
	{
		for (int j = 0; j < t_room.M_TOTALWIDTH; j++)
		{
			if (t_body.getGlobalBounds().intersects(t_room.m_tiles[i][j].m_bodySquare.getGlobalBounds()))
			{
				if (t_room.m_tiles[i][j].m_type == TileType::DOOR &&
					t_room.m_tiles[i][j].isDoorOpen
					&& m_control.m_currentState.Y)
				{
					std::cout << currentRoom << std::endl;
					if (currentRoom != 12)
					{
						t_room.m_tiles[i][j].isDoorOpen = false;
						std::string str = "Assets\\Levels\\Level" + std::to_string(currentRoom) + ".txt";
						t_room.loadFile(str);
						currentRoom++;
						resetEnemies = true;
						t_room.render();
					}
				}
				else if (t_room.m_tiles[i][j].m_type == TileType::DOOR &&
					!t_room.m_tiles[i][j].isDoorOpen
					&& m_control.m_currentState.X && !t_bossAlive)
				{
					if (currentRoom == 6)
					{
						if (m_pickUps.m_keyOwned = true)
						{
							t_room.m_tiles[i][j].isDoorOpen = true;
							std::string str = "Assets\\Levels\\Level" + std::to_string(currentRoom) + ".txt";
							t_room.loadFile(str);
							currentRoom++;
							t_room.render();
						}
					}
					else if (currentRoom == 12)
					{
						m_levelEnd = true;
					}
					else
					{
						t_room.m_tiles[i][j].isDoorOpen = true;
					}
					
					t_room.m_tiles[i][j].updateTexture();
				}

				if (t_room.m_tiles[i][j].m_type == TileType::WALL || t_room.m_tiles[i][j].m_type == TileType::LIGHT)
				{
					m_position = m_prevPos;
					t_body.setPosition(m_position);
				}// !if
			}// !if
		}// !for
	}// !for

}// !checkTileCollision

void Player::checkTileCollisionWithBullet(RoomBuilder & t_room)
{
	for (int i = 0; i < t_room.M_TOTALHEIGHT; i++)
	{
		for (int j = 0; j < t_room.M_TOTALWIDTH; j++)
		{
			if (m_pool.checkCollision(t_room.m_tiles[i][j].m_bodySquare) && t_room.m_tiles[i][j].m_type == TileType::WALL)
			{
					m_pool.setSpeed(0.0);
			}// !if
		}// !for
	}// !for

}

void Player::checkEnemyCollisionWithBullet(sf::RectangleShape &t_enemy, bool &t_alive)
{
	if (m_pool.m_speed != sf::Vector2f(0, 0))
	{
		if (m_pool.checkCollision(t_enemy))
		{
			if (m_enemyHitSound.getStatus() != sf::Sound::Playing)
			{
				m_enemyHitSound.play();
			}

			//m_pool.setSpeed(0.0);
			t_alive = false;

			m_particleSystem.init(m_pool.returnInUse().getPosition());
			randomNum = std::rand() % 10;
			m_pickUpDropped = true;
			switch (randomNum)
			{
			case 0:
				m_pickUps.heartPosition(t_enemy.getPosition());
				break;
			case 5:
				m_pickUps.starPosition(t_enemy.getPosition());
				break;
			}

			if (currentRoom == 5)
			{
				m_pickUps.keyPosition(t_enemy.getPosition());
			}
		}
	}
}


void Player::checkBossCollisionWithBullet(sf::RectangleShape &t_enemy, bool &t_alive)
{
	if (m_pool.checkCollision(t_enemy))
	{
		if (m_enemyHitSound.getStatus() != sf::Sound::Playing)
		{
			m_enemyHitSound.play();
		}

		m_particleSystem.init(m_pool.returnInUse().getPosition());
		m_pool.setSpeed(0.0);
		bossHealth -= 2;
		if (bossHealth <= 0)
		{
			t_alive = false;
		}
	}
}

void Player::checkEnemyCollisionWithPlayer(sf::RectangleShape  t_enemy)
{
	if(t_enemy.getGlobalBounds().intersects(m_body.getGlobalBounds()))
	{
		m_hitSound.play();
		collisionTimer++;
		if (collisionTimer == 100)
		{
			m_lives--;
			collisionTimer = 0;
		}
	}
}
void Player::checkPickUpStarCollision(sf::Sprite t_pickup)
{
	if (t_pickup.getGlobalBounds().intersects(m_body.getGlobalBounds()) && m_control.m_currentState.A)
	{
		m_pickUps.m_pickedUp = true;
		m_pickUps.m_star.setPosition(2000, 2000);
		m_pickUps.starCollision();

	}
}
// !checkTileCollision

void Player::checkPickUpHeartCollision(sf::Sprite t_pickup)
{
	if (t_pickup.getGlobalBounds().intersects(m_body.getGlobalBounds()) && m_control.m_currentState.A)
	{
		m_lives += 1;
		m_pickUps.m_heart.setPosition(2000, 2000);
		m_pickUps.heartCollision();
	}
}

void Player::checkPickUpKeyCollision(sf::Sprite t_pickup)
{
	if (t_pickup.getGlobalBounds().intersects(m_body.getGlobalBounds()) && m_control.m_currentState.A)
	{
		m_pickUps.keyCollision();
		m_pickUps.m_key.setPosition(2000, 2000);
	}
}

void Player::fire()
{
	if (m_body.getScale().x > 0)
	{
		sf::Vector2f firePosition(m_body.getPosition().x + m_body.getLocalBounds().width, m_body.getPosition().y + m_body.getLocalBounds().height / 2 + 30);
		m_pool.create(firePosition, m_bulletSpeed, m_angle, m_bulletTexture);
	}//!if
}//!fore

void Player::playerShooting(double const & t_dt)
{
	if (m_control.m_currentState.RTrigger > 0 && !m_requestFire)
	{
		if (m_knifeSound.getStatus() != sf::Sound::Playing)
		{
			m_knifeSound.play();
		}
		m_time = m_waitTime;
		m_requestFire = true;
		fire();
	}//!if
	m_pool.update(t_dt);
}

//!playerShooting
void Player::render(sf::RenderWindow & t_window)
{
	m_pickUps.HUDrender(t_window);
	if (m_pickUpDropped == true)
	{
		m_pickUps.render(t_window);
	}
	m_particleSystem.render(t_window);

	m_pool.render(t_window);
	t_window.draw(m_body);
	//m_light.render(t_window);
} // !render

void Player::reset()
{
	currentRoom = 2;
	m_lives = 3;
	m_position = sf::Vector2f(300, 300);
	m_prevPos = m_position;
	collisionTimer = 0;
	bossHealth = 20;
	m_currentState = PlayerState::IDLEDOWN;
	m_previousState = PlayerState::IDLEDOWN;
	m_alive = true;
	m_levelEnd = false;
	m_bulletSpeed = sf::Vector2f(0.5,0.5);
}

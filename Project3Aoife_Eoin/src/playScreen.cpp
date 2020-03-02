#include "playScreen.h"

playScreen::playScreen(ResourceManager & t_resourceMan, sf::RenderWindow & t_window, Xbox360Controller & t_control) :
	m_controller(t_control),
	m_window(t_window),
	m_resManager(t_resourceMan), 
	m_roomBuilder(m_window, t_resourceMan),
	m_player(sf::Vector2f(54, 54), sf::Vector2f(300, 300), t_control, t_resourceMan),
	m_levelEndScreen(m_roomBuilder, t_resourceMan, t_window, t_control),
	m_loseScreen(t_resourceMan)
{
	m_gameView.setSize(1600, 1080);
	m_gameView.setCenter(sf::Vector2f((GlobalSettings::s_width * .5) - 150, (GlobalSettings::s_height * .5) - 130));
	m_window.setView(m_gameView);

	m_roomBuilder.loadFile("Assets\\Levels\\Tutorial.txt");

	m_tutorialSprite.setPosition(200, 200);
	m_tutorialSprite.setTexture(m_resManager.m_tutorial1);
	m_tutorialSprite.setScale(1.5, 1.5);

	m_enemy[0].dontMove = true;
	m_enemy[1].dontMove = true;

	m_bossEnemy.m_alive = false;
	m_bossEnemy.m_position = sf::Vector2f(2000, 2000);
	m_bossEnemy.m_body.setTexture(&m_resManager.m_spiderIdleUp);

	for (int i = 0; i < 3; i++)
	{
		m_livesHUD[i].setPosition(20 + (10 * i) * 5, -75);
		m_livesHUD[i].setScale(0.2, 0.2);
		m_livesHUD[i].setTexture(m_resManager.m_heart);
	}
}// !playScreen

playScreen::~playScreen()
{
}// !~playScreen

void playScreen::update(double t_dt)
{
	m_player.update(t_dt, m_roomBuilder);

	setupEnemies(t_dt);

	//check enemy collisions
	for (int i = 0; i < 4; i++)
	{
		if (m_enemy[i].m_alive)
		{
			m_player.checkEnemyCollisionWithBullet(m_enemy[i].m_body, m_enemy[i].m_alive);
			m_player.checkEnemyCollisionWithPlayer(m_enemy[i].m_body);
			m_enemy[i].checkEnemyTileCollision(m_roomBuilder);
			m_enemy[i].checkPlayerCollisionWithBullet(m_player.m_body, m_player.m_lives, m_player.m_hitSound);
			m_enemy[i].checkTileCollisionWithBullet(m_roomBuilder);
		}
	}

	//check player collisions
	m_player.checkTileCollision(m_roomBuilder, m_player.m_body, m_bossEnemy.m_alive);
	m_player.checkTileCollisionWithBullet(m_roomBuilder);

	if (!m_bossEnemy.m_alive)
	{
		m_bossEnemy.m_position = sf::Vector2f{ 20000, 20000 };
	}

	for (int i = 0; i < 4; i++)
	{
		if (!m_enemy[i].m_alive)
		{
			m_enemy[i].m_position = sf::Vector2f{ 2000,2000 };
		}
	}

	if (m_bossEnemy.m_alive)
	{
		m_bossEnemy.checkEnemyTileCollision(m_roomBuilder);
		m_bossEnemy.checkPlayerCollisionWithBullet(m_player.m_body, m_player.m_lives, m_player.m_hitSound);
		
		m_bossEnemy.updateEnemyFollow(t_dt, m_roomBuilder, m_player.m_position);
		m_bossEnemy.bossHealth(m_player.bossHealth);
		m_player.checkBossCollisionWithBullet(m_bossEnemy.m_body, m_bossEnemy.m_alive);
		m_player.checkEnemyCollisionWithPlayer(m_bossEnemy.m_body);
	}

	if (m_player.m_levelEnd)
	{
		m_levelEndScreen.m_isShown = true;
		m_levelEndScreen.update(t_dt, m_player);
		if (m_controller.m_currentState.A)
		{
			m_player.m_levelEnd = false;
			resetLevel();
		}
	
	}
	if (!m_levelEndScreen.m_isShown)
	{
		m_player.m_levelEnd = false;
	}

	HUD();

	if (m_controller.m_currentState.Start)
	{
		m_switchPause = true;
	}

}
void playScreen::HUD()
{
	if (m_player.m_lives == 3)
	{
		m_livesHUD[2].setTexture(m_resManager.m_heart);
		m_livesHUD[1].setTexture(m_resManager.m_heart);
		m_livesHUD[0].setTexture(m_resManager.m_heart);
	}
	if (m_player.m_lives == 2.5)
	{
		m_livesHUD[2].setTexture(m_resManager.m_halfHeart);
	}
	if (m_player.m_lives == 2)
	{
		m_livesHUD[2].setTexture(m_resManager.m_emptyHeart);
	}

	if (m_player.m_lives == 1.5)
	{
		m_livesHUD[1].setTexture(m_resManager.m_halfHeart);
	}
	if (m_player.m_lives == 1)
	{
		m_livesHUD[1].setTexture(m_resManager.m_emptyHeart);
	}

	if (m_player.m_lives == 0.5)
	{
		m_livesHUD[0].setTexture(m_resManager.m_halfHeart);
	}
	if (m_player.m_lives == 0)
	{
		m_livesHUD[0].setTexture(m_resManager.m_emptyHeart);
	}
}
// !update

void playScreen::render()
{
	m_window.clear();
	m_roomBuilder.render();
	for (int i = 0; i < 3; i++)
	{
		m_window.draw(m_livesHUD[i]);
	}
	if (m_player.currentRoom == 1)
	{
		m_window.draw(m_tutorialSprite);
	}
	m_player.render(m_window);

	if (m_player.currentRoom >= 2)
	{
		for (int i = 0; i < 4; i++)
		{
			m_enemy[i].render(m_window);
		}
	}
	if (m_bossEnemy.m_alive)
	{
		m_bossEnemy.render(m_window);
	}
	
	m_roomBuilder.m_lighting.render(m_window);

	if (m_levelEndScreen.m_isShown)
	{
		m_levelEndScreen.render();
	}

	if(!m_player.m_alive)
	{
		if(m_controller.m_currentState.A)
		{
			resetLevel();
		}
		m_loseScreen.render(m_window);
	}
}

void playScreen::loadNewLevel(std::string t_roomName)
{
	m_roomBuilder.loadFile(t_roomName);

	if (m_player.currentRoom == 2)
	{
		m_enemy[0].m_position = { 1000,500 };
	}
}
void playScreen::setupEnemies(double t_dt)
{
	if (m_player.currentRoom != 1)
	{
		for (int i = 0; i < 2; i++)
		{
			m_enemy[i].updateEnemyShoot(t_dt, m_roomBuilder, m_player.m_position);
		}
		m_enemy[2].updateEnemyFollowShoot(t_dt, m_roomBuilder, m_player.m_position);
		m_enemy[3].updateEnemyFollow(t_dt, m_roomBuilder, m_player.m_position);
		if (m_bossEnemy.m_alive)
		{
			m_bossEnemy.updateBoss(t_dt, m_roomBuilder, m_player.m_position);
		}
	}

	if (m_player.currentRoom == 1)
	{
		if (m_player.resetEnemies)
		{
			m_enemy[0].m_body.setPosition(2000, 2000);
			m_enemy[1].m_body.setPosition(2000, 2000);
			m_enemy[2].m_body.setPosition(2000, 2000);
			m_enemy[3].m_body.setPosition(2000, 2000);
			m_bossEnemy.m_body.setPosition(20000, 20000);
		}
	}

	if (m_player.currentRoom == 2)
	{
		if (m_player.resetEnemies)
		{
			m_enemy[0].m_body.setPosition(300, 600);
			m_enemy[1].m_body.setPosition(1200, 200);
			m_enemy[2].m_body.setPosition(100, 100);
			m_enemy[3].m_body.setPosition(1000, 500);
		}
		m_player.resetEnemies = false;
	}

	if (m_player.currentRoom == 3)
	{
		if (m_player.resetEnemies)
		{
			for (int i = 0; i < 4; i++)
			{
				m_enemy[i].m_alive = true;
			}
			m_enemy[0].m_body.setPosition(1350, 150);
			m_enemy[1].m_body.setPosition(1000, 650);
			m_enemy[2].m_body.setPosition(200, 650);
			m_enemy[3].m_body.setPosition(400, 200);
		}
		m_player.resetEnemies = false;
	}

	if (m_player.currentRoom == 4)
	{
		if (m_player.resetEnemies)
		{
			for (int i = 0; i < 2; i++)
			{
				m_enemy[i].m_alive = true;
			}
			m_enemy[0].m_body.setPosition(1350, 650);
			m_enemy[1].m_body.setPosition(200, 200);
			m_enemy[2].m_body.setPosition(2000, 2000);
			m_enemy[3].m_body.setPosition(2000, 2000);
		}
		m_player.resetEnemies = false;
	}

	if (m_player.currentRoom == 5)
	{
		if (m_player.resetEnemies)
		{
			for (int i = 0; i < 3; i++)
			{
				m_enemy[i].m_alive = true;
			}
			m_enemy[0].m_body.setPosition(1350, 600);
			m_enemy[1].m_body.setPosition(200, 600);
			m_enemy[2].m_body.setPosition(1350, 200);
			m_enemy[3].m_body.setPosition(2000, 2000);
		}
		m_player.resetEnemies = false;
	}

	if (m_player.currentRoom == 6)
	{
			for (int i = 0; i < 3; i++)
			{
				m_enemy[i].m_alive = false;
				m_enemy[i].m_body.setPosition(20000, 20000);
			}
			
		m_player.resetEnemies = false;
	}

	if (m_player.currentRoom == 8)
	{
		for (int i = 0; i < 4; i++)
		{
			m_enemy[i].m_alive = true;
		}
		m_player.bossHealth = 40;
		m_enemy[0].m_body.setPosition(1350, 600);
		m_enemy[1].m_body.setPosition(200, 600);
		m_enemy[2].m_body.setPosition(1350, 200);
		m_enemy[3].m_body.setPosition(800, 600);


		m_player.resetEnemies = false;
	}

	if (m_player.currentRoom == 9)
	{
		for (int i = 0; i < 2; i++)
		{
			m_enemy[i].m_alive = true;
		}

		m_enemy[0].m_body.setPosition(1350, 300);
		m_enemy[1].m_body.setPosition(200, 600);
		m_enemy[2].m_body.setPosition(2000, 2000);
		m_enemy[3].m_body.setPosition(2000, 2000);


		m_player.resetEnemies = false;
	}

	if (m_player.currentRoom == 10)
	{
		for (int i = 0; i < 2; i++)
		{
			m_enemy[i].m_alive = true;
		}

		m_enemy[0].m_body.setPosition(1350, 150);
		m_enemy[1].m_body.setPosition(1150, 150);
		m_enemy[2].m_body.setPosition(300, 150);
		m_enemy[3].m_body.setPosition(550, 200);

		m_player.resetEnemies = false;
	}

	if (m_player.currentRoom == 11)
	{
		for (int i = 0; i < 3; i++)
		{
			m_enemy[i].m_alive = false;
			m_enemy[i].m_body.setPosition(20000, 20000);
		}
		m_player.resetEnemies = false;
	}

	if (m_player.currentRoom == 7 || m_player.currentRoom == 12)
	{
			m_bossEnemy.m_body.setPosition(sf::Vector2f(300, 200));
			m_bossEnemy.m_alive = true;
			m_bossEnemy.updateEnemyFollow(t_dt, m_roomBuilder, m_player.m_position);

			m_enemy[0].m_body.setPosition(2000, 2000);
			m_enemy[1].m_body.setPosition(2000, 2000);
			m_enemy[2].m_body.setPosition(2000, 2000);
			m_enemy[3].m_body.setPosition(2000, 2000);

			m_bossEnemy.bossHealth(m_player.bossHealth);

			if (m_player.bossHealth <= 0)
			{
				m_bossEnemy.m_alive = false;
				m_bossEnemy.m_position = sf::Vector2f{ 20000, 20000 };
			}
		
	}
}
void playScreen::resetLevel()
{
	m_player.reset();
	m_livesHUD[2].setTexture(m_resManager.m_heart);
	m_livesHUD[1].setTexture(m_resManager.m_heart);
	m_livesHUD[0].setTexture(m_resManager.m_heart);

	m_roomBuilder.loadFile("Assets\\Levels\\Level" + std::to_string(m_player.currentRoom)+".txt");
	m_roomBuilder.render();
	
	for (int i = 0; i < 4; i++)
	{
		m_enemy[i].reset();
	}
	m_bossEnemy.m_position = sf::Vector2f(2000, 2000);
	m_bossEnemy.m_prevPosition = m_bossEnemy.m_position;
	m_bossEnemy.m_alive = false;

}
// !render

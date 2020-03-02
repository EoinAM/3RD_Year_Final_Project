#ifndef GAME
#define GAME

#include "RoomBuilder.h"
#include "SceneManager.h"

class Game
{
public: //Functions
	Game(sf::RenderWindow & t_window);
	~Game();
	void run();

private: //Functions
	void processEvents();
	void processGameEvents(sf::Event & t_event);
	void update(double t_dt);
	void render();

public : //Variables
	sf::Font m_font;
	sf::RenderWindow & m_window;
private: //Variables

	sf::View m_gameScreenView;
	
	ResourceManager m_resManager;
	SceneManager m_sceneManger;
};

#endif // !GAME



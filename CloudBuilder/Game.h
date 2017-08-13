#pragma once

#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
//#include <SFML\Network.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include "StateMachine.h"
#include "ResourceHandler.h"

class InstructionSquare;

class Game
{
public:
	//struct GameContext
	//{
	//	GameContext(StateMachine& sm, ResourceHandler& rh) : stateMachine(sm), resourceHandler(rh) {}

	//	StateMachine& stateMachine;
	//	ResourceHandler& resourceHandler;
	//};

	Game();
	~Game();

	void run();

	void test();

private:
	void initialize();

	void processEvents();
	void handleEvent(const sf::Event& event);
	void update(sf::Time dt);
	void draw();

private:
	sf::RenderWindow mWindow;
	StateMachine mStateMachine;
	ResourceHandler mResourceHandler;
};


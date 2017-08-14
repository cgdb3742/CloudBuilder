#pragma once

#include <memory>
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
//#include <SFML\Network.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include "StateMachine.h"
#include "ResourceHandler.h"
#include "CompleteData.h"

class InstructionSquare;

struct GameContext
{
	GameContext(ResourceHandler& rh, GameData& gd, LevelData& ld) : resourceHandler(rh), gameData(gd), levelData(ld) {}

	//StateMachine& stateMachine;
	ResourceHandler& resourceHandler;
	GameData& gameData;
	LevelData& levelData;
};

class Game
{
public:
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
	GameContext mContext;
	CompleteData mData;
};


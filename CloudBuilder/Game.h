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
#include "PopUpStack.h"

class InstructionSquare;

struct GameContext
{
	GameContext(ResourceHandler& rh, PopUpStack& pus, GameData& gd, LevelData& ld) : resourceHandler(rh), popUpStack(pus), gameData(gd), levelData(ld) {}

	//StateMachine& stateMachine;
	ResourceHandler& resourceHandler;
	PopUpStack& popUpStack;
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
	PopUpStack mPopUpStack;
	GameContext mContext;
	CompleteData mData;
};


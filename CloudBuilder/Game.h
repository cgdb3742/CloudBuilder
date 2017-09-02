#pragma once

#include <memory>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
//#include <SFML\Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "StateMachine.h"
#include "ResourceHandler.h"
#include "CompleteData.h"
#include "StateRequestStack.h"
#include "PopUpStack.h"

class InstructionSquare;

struct GameContext
{
	GameContext(ResourceHandler& rh, StateRequestStack& srs, PopUpStack& pus, CompleteData& cd) : resourceHandler(rh), stateStack(srs), popUpStack(pus), dataReader(cd), saveData(cd.getSaveData()), gameData(cd.getGameData()), levelData(cd.getLevelData()) {}

	//StateMachine& stateMachine;
	ResourceHandler& resourceHandler;
	StateRequestStack& stateStack;
	PopUpStack& popUpStack;
	CompleteData& dataReader;
	SaveData& saveData;
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
	StateRequestStack mStateStack;
	PopUpStack mPopUpStack;
	GameContext mContext;
	CompleteData mData;
};


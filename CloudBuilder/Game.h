#pragma once

#include <memory>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
//#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "StateMachine.h"
#include "ResourceHandler.h"
#include "CompleteData.h"
#include "StateRequestStack.h"
#include "PopUpStack.h"
#include "ParticleHandler.h"
#include "ClipboardControl.h"

//class InstructionSquare;

struct GlobalInfos
{
	GlobalInfos() : debugMode(false), system(ClipboardControl::System::Unsupported) {}
	GlobalInfos(ClipboardControl::System sys) : debugMode(false), system(sys) {}
	GlobalInfos(bool debug, ClipboardControl::System sys) : debugMode(debug), system(sys) {}

	bool debugMode;
	ClipboardControl::System system;
};

struct GameContext
{
	GameContext(ResourceHandler& rh, ParticleHandler& ph, StateRequestStack& srs, PopUpStack& pus, CompleteData& cd, ClipboardControl& cc, GlobalInfos& gi) : resourceHandler(rh), particleHandler(ph), stateStack(srs), popUpStack(pus), dataReader(cd), saveData(cd.getSaveData()), gameData(cd.getGameData()), levelData(cd.getLevelData()), clipboardControl(cc), globalInfos(gi) {}

	//StateMachine& stateMachine;
	ResourceHandler& resourceHandler;
	ParticleHandler& particleHandler;
	StateRequestStack& stateStack;
	PopUpStack& popUpStack;
	CompleteData& dataReader;
	SaveData& saveData;
	GameData& gameData;
	LevelData& levelData;
	ClipboardControl& clipboardControl;

	GlobalInfos& globalInfos;
};

class Game
{
public:
	Game(GlobalInfos infos);
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
	ParticleHandler mParticleHandler;
	StateRequestStack mStateStack;
	PopUpStack mPopUpStack;
	GameContext mContext;
	CompleteData mData;
	ClipboardControl mClipboardControl;
	
	GlobalInfos mInfos;
};


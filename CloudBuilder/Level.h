#pragma once

#include <map>
#include <utility>
#include "GameEntity.h"
#include "BuildLockable.h"
#include "RobotPair.h"
#include "InstructionMouseDragHandler.h"
#include "GUILevelMenu.h"
#include "InstructionPlayer.h"

class Level :
	public GameEntity,
	public BuildLockable
{
public:
	Level(GameContext& gameContext);
	Level(GameContext& gameContext, unsigned int nbRobots);
	~Level();

	void createRobotPairs(unsigned int nb);

	bool createStartInstructionSpace(unsigned int i, unsigned int j, Enums::eColor color);

	virtual void lock();
	virtual void unlock();

	void resetAll();

	virtual void updateCurrent(sf::Time dt);

	virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);
protected:
	virtual void updateChildsVector();
private:
	bool mIsRunning; //false if building code, true if testing code
	std::map<Enums::eColor,RobotPair> mRobots;
	CloudCanvas mCanvas;
	InstructionBoard mBoard;
	//GUIInstructionCreatorContainer mCreatorContainer;
	GUILevelMenu mMenu;
	InstructionMouseDragHandler mInstructionDragger;
	InstructionPlayer mPlayer;
};


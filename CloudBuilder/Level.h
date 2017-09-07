#pragma once

#include <map>
#include <utility>
#include "GameEntity.h"
#include "BuildLockable.h"
#include "RobotControl.h"
#include "InstructionMouseDragHandler.h"
#include "GUILevelMenu.h"
#include "InstructionPlayer.h"
#include "HiddenVerifier.h"

struct LevelData;

class Level :
	public GameEntity,
	public BuildLockable
{
public:
	Level(GameContext& gameContext);
	Level(GameContext& gameContext, LevelData levelData);
	Level(GameContext& gameContext, unsigned int nbRobots);
	~Level();

	bool createStartInstructionSpace(unsigned int i, unsigned int j, Enums::eColor color);

	void createBaseReports(LevelData data);

	virtual void lock();
	virtual void unlock();

	void resetBoardFromStart();
	void resetAll();

	unsigned int getCurrentCloud();
	void changeCurrentCloud(unsigned int newCloud);
	void changeToNextCloud();
	void changeToPreviousCloud();

	void runVerifications();

	bool saveBoard();

	virtual void updateCurrent(sf::Time dt);

	virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);
protected:
	virtual void updateChildsVector();
private:
	unsigned int mCurrentCloud;
	//bool mIsRunning; //false if building code, true if testing code
	//std::map<Enums::eColor,RobotPair> mRobots;
	RobotControl mRobots;
	CloudCanvas mCanvas;
	InstructionBoard mBoard;
	//GUIInstructionCreatorContainer mCreatorContainer;
	GUILevelMenu mMenu;
	InstructionMouseDragHandler mInstructionDragger;
	InstructionPlayer mPlayer;
	std::list<VerificationReport> mBaseReports;
};


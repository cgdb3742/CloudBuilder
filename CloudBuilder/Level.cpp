#include <iostream>
#include "Level.h"
#include "Game.h"


Level::Level(GameContext & gameContext):
	GameEntity(gameContext),
	mCurrentCloud(0),
	mCanvas(gameContext, gameContext.levelData.clouds[mCurrentCloud]), //TODO Choosing cloud
	mBoard(gameContext),
	//mIsRunning(false),
	mPlayer(gameContext, *this, mRobots),
	mMenu(gameContext, *this, mBoard, mPlayer),
	mInstructionDragger(gameContext, mBoard, mMenu.getCreator())
{
	std::cout << "Creating GameEntity : Level." << std::endl;

	mBoard.loadLevelBoard(gameContext.levelData.world, gameContext.levelData.level);

	createRobotPairs(gameContext.levelData.nbRobots);
	createBaseReports(gameContext.levelData);

	mGameContext.resourceHandler.changeAndPlayMusic(gameContext.levelData.music, false);
	//mMenu.changeSelection(0);

	//std::cout << mCanvas.convertToString() << std::endl;
}

Level::Level(GameContext & gameContext, LevelData levelData) :
	GameEntity(gameContext),
	mCurrentCloud(0),
	mCanvas(gameContext, levelData.clouds[mCurrentCloud]), //TODO Choosing cloud
	mBoard(gameContext),
	//mIsRunning(false),
	mPlayer(gameContext, *this, mRobots),
	mMenu(gameContext, *this, mBoard, mPlayer),
	mInstructionDragger(gameContext, mBoard, mMenu.getCreator())
{
	mBoard.loadLevelBoard(levelData.world, levelData.level);

	createRobotPairs(levelData.nbRobots);
	createBaseReports(levelData);

	mGameContext.resourceHandler.changeAndPlayMusic(levelData.music, false);
}

Level::Level(GameContext & gameContext, unsigned int nbRobots) :
	GameEntity(gameContext),
	mCurrentCloud(0),
	mCanvas(gameContext, gameContext.levelData.clouds[mCurrentCloud]), //TODO Choosing cloud
	mBoard(gameContext),
	//mIsRunning(false),
	mPlayer(gameContext, *this, mRobots),
	mMenu(gameContext, *this, mBoard, mPlayer),
	mInstructionDragger(gameContext, mBoard, mMenu.getCreator())
{
	std::cout << "Creating GameEntity : Level." << std::endl;

	mBoard.loadLevelBoard(gameContext.levelData.world, gameContext.levelData.level);

	createRobotPairs(nbRobots);
	createBaseReports(gameContext.levelData);

	mGameContext.resourceHandler.changeAndPlayMusic(gameContext.levelData.music, false);
	//mMenu.changeSelection(0);

	//std::cout << mCanvas.convertToString() << std::endl;
	//std::cout << mCanvas.convertFromString(mCanvas.convertToString()) << std::endl;
	//std::cout << mCanvas.convertToString() << std::endl;
	//std::cout << mBoard.convertToString() << std::endl;
	//std::cout << mBoard.convertFromString(mBoard.convertToString()) << std::endl;
	//std::cout << mBoard.convertToString() << std::endl;
}

Level::~Level()
{
}

void Level::createRobotPairs(unsigned int nb)
{
	if (nb < 1) nb = 1;
	if (nb > 4) nb = 4;

	mRobots.clear();

	for (unsigned int i = 1; i <= nb; i++)
	{
		Enums::eColor color;

		switch (i)
		{
		case 1: color = Enums::eColor::Red; break;
		case 2: color = Enums::eColor::Blue; break;
		case 3: color = Enums::eColor::Green; break;
		case 4: color = Enums::eColor::Yellow; break;
		default: color = Enums::eColor::Red; break;
		}

		mRobots.insert(std::pair<Enums::eColor, RobotPair>(color, RobotPair(mGameContext, mCanvas, mBoard, color)));
		//mRobots.push_back(RobotPair(mCanvas, mBoard, color));
		//mRobots.push_back(RobotPair(mCanvas, mBoard, Enums::eColor::Yellow));
	}
}

//TODO Unused ? Use when board loaded from string is incomplete ?
bool Level::createStartInstructionSpace(unsigned int i, unsigned int j, Enums::eColor color)
{
	
	return false;
}

void Level::createBaseReports(LevelData data)
{
	mBaseReports.clear();

	for (unsigned int i = 0; i < data.clouds.size(); i++)
	{
		if (data.isValidation)
		{
			mBaseReports.push_back(VerificationReport(CloudPicture(mGameContext, data.clouds[i]), (data.results[i] == "Accept") ? Enums::eResult::Accept : Enums::eResult::Refuse));
		}
		else
		{
			mBaseReports.push_back(VerificationReport(CloudPicture(mGameContext, data.clouds[i]), CloudPicture(mGameContext, data.results[i])));
		}
	}
}

void Level::lock()
{
	BuildLockable::lock();
	mBoard.lock();
	mMenu.lock();
	mInstructionDragger.lock();
}

void Level::unlock()
{
	BuildLockable::unlock();
	mBoard.unlock();
	mMenu.unlock();
	mInstructionDragger.unlock();
}

void Level::resetBoardFromStart()
{
	if (isLocked())
	{
		return;
	}

	mInstructionDragger.drop();
	mBoard.convertFromString(mGameContext.levelData.startingBoard);

	resetAll();
}

void Level::resetAll()
{
	if (isLocked())
	{
		return;
	}

	mCanvas.convertFromString(mGameContext.levelData.clouds[mCurrentCloud]);

	//updateChildsVectorAll();
	setPositionAll(mTopLeftCorner, mBoundingBox);

	for (auto& pair : mRobots)
	{
		pair.second.resetAll();
	}
}

unsigned int Level::getCurrentCloud()
{
	return mCurrentCloud;
}

void Level::changeCurrentCloud(unsigned int newCloud)
{
	if (newCloud < 0 || newCloud >= mGameContext.levelData.clouds.size() || isLocked())
	{
		return;
	}
	else
	{
		mCurrentCloud = newCloud;
		mCanvas.convertFromString(mGameContext.levelData.clouds[mCurrentCloud]);
		setPositionAll(mTopLeftCorner, mBoundingBox);
	}
}

void Level::changeToNextCloud()
{
	if (mCurrentCloud == mGameContext.levelData.clouds.size() - 1)
	{
		changeCurrentCloud(0);
	}
	else
	{
		changeCurrentCloud(mCurrentCloud + 1);
	}
}

void Level::changeToPreviousCloud()
{
	if (mCurrentCloud == 0)
	{
		changeCurrentCloud(mGameContext.levelData.clouds.size() - 1);
	}
	else
	{
		changeCurrentCloud(mCurrentCloud - 1);
	}
}

//TODO Multithreading
void Level::runVerifications()
{
	std::vector<VerificationReport> endReports;

	for (VerificationReport& baseReport : mBaseReports)
	{
		HiddenVerifier verifier(mGameContext, baseReport, mBoard, mRobots.size());
		verifier.play(10000); //TODO test steps number
		endReports.push_back(verifier.getReport());
	}

	if (!endReports[mCurrentCloud].isCorrectResult)
	{
		mGameContext.popUpStack.addMessage(mGameContext.gameData.levelResultMessage[1], mGameContext.gameData.levelResultButton[1]);
	}
	else
	{
		VerificationReport failedReport = endReports[0];
		bool hasFailed = false;
		unsigned int failureId = 0;

		for (unsigned int i = 0; i < mGameContext.levelData.clouds.size(); i++)
		{
			if (!endReports[i].isCorrectResult)
			{
				failedReport = endReports[i];
				hasFailed = true;
				failureId = i;
			}
		}

		if (hasFailed)
		{
			mGameContext.popUpStack.addMessage(mGameContext.gameData.levelResultMessage[2], mGameContext.gameData.levelResultButton[2]);

			changeCurrentCloud(failureId);
			resetAll();
		}
		else
		{
			mGameContext.popUpStack.addMessage(mGameContext.gameData.levelResultMessage[0], mGameContext.gameData.levelResultButton[0]);
		}
	}

	//TODO Use the report to clear level
}

bool Level::saveBoard()
{
	return mGameContext.dataReader.writeSavedBoard(mGameContext.levelData.world, mGameContext.levelData.level, mBoard.convertToString());
}

void Level::updateCurrent(sf::Time dt)
{
	if (mBoard.hasUpdatedStartPoints()) //Note : can only happen in build mode
	{
		for (auto& rb : mRobots)
		{
			rb.second.startPointsUpdated();
		}
	}
}

void Level::setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	mCanvas.setPositionAll(minCorner, sf::Vector2f(maxBox.x / 2.0f, maxBox.y * 3.0f / 4.0f));
	mBoard.setPositionAll(sf::Vector2f(minCorner.x + maxBox.x / 2.0f, minCorner.y), sf::Vector2f(maxBox.x / 2.0f, maxBox.y * 3.0f / 4.0f));
	mMenu.setPositionAll(sf::Vector2f(minCorner.x, minCorner.y + maxBox.y * 3.0f / 4.0f), sf::Vector2f(maxBox.x, maxBox.y / 4.0f));
	mInstructionDragger.setPositionAll(minCorner, maxBox);
	mPlayer.setPositionAll(minCorner, maxBox);

	//for (RobotPair& rb : mRobots)
	for (auto& rb : mRobots)
	{
		rb.second.setPositionAll(minCorner, maxBox);
	}
}

void Level::updateChildsVector()
{
	mChilds.clear();
	mChilds.push_back(mCanvas);
	mChilds.push_back(mBoard);

	for (auto& rb : mRobots)
	{
		mChilds.push_back(rb.second);
	}

	mChilds.push_back(mMenu);
	mChilds.push_back(mInstructionDragger);
	mChilds.push_back(mPlayer);
}

#include <iostream>
#include "Level.h"
#include "Game.h"


Level::Level(GameContext & gameContext) :
	GameEntity(gameContext),
	mCurrentCloud(0),
	mCanvas(gameContext, gameContext.levelData.clouds[mCurrentCloud]), //TODO Choosing cloud
	mBoard(gameContext),
	//mIsRunning(false),
	mPlayer(gameContext, *this, mRobots),
	mMenu(gameContext, *this, mBoard, mPlayer),
	mInstructionDragger(gameContext, mBoard, mMenu.getCreator()),
	mRobots(gameContext, mCanvas, mBoard, gameContext.levelData.nbRobots, true),
	mDebugMode(true)
{
	std::cout << "Creating GameEntity : Level." << std::endl;

	mBoard.loadLevelBoard(gameContext.levelData.world, gameContext.levelData.level);

	createBaseReports(gameContext.levelData);
	mGameContext.dataReader.writeLevelStatus(mGameContext.levelData.world, mGameContext.levelData.level, Enums::eLevelStatus::Available);

	mRobots.createRobotPairs();

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
	mInstructionDragger(gameContext, mBoard, mMenu.getCreator()),
	mRobots(gameContext, mCanvas, mBoard, levelData.nbRobots, true),
	mDebugMode(true)
{
	mBoard.loadLevelBoard(levelData.world, levelData.level);

	createBaseReports(levelData);
	mGameContext.dataReader.writeLevelStatus(mGameContext.levelData.world, mGameContext.levelData.level, Enums::eLevelStatus::Available);

	mRobots.createRobotPairs();

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
	mInstructionDragger(gameContext, mBoard, mMenu.getCreator()),
	mRobots(gameContext, mCanvas, mBoard, gameContext.levelData.nbRobots, true),
	mDebugMode(true)
{
	std::cout << "Creating GameEntity : Level." << std::endl;

	mBoard.loadLevelBoard(gameContext.levelData.world, gameContext.levelData.level);

	createBaseReports(gameContext.levelData);
	mGameContext.dataReader.writeLevelStatus(mGameContext.levelData.world, mGameContext.levelData.level, Enums::eLevelStatus::Available);

	mRobots.createRobotPairs();

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

	mRobots.resetAll();
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
		//HiddenVerifier verifier(mGameContext, baseReport, mBoard, mRobots.size());
		HiddenVerifier verifier(mGameContext, baseReport, mBoard, mGameContext.levelData.nbRobots);
		verifier.play(10000); //TODO test steps number
		endReports.push_back(verifier.getReport());
	}

	if (!endReports[mCurrentCloud].isCorrectResult)
	{
		//Failure
		mGameContext.popUpStack.addMessage(mGameContext.gameData.popUpMessage[1], mGameContext.gameData.popUpButton[1]);
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
			//Hidden failure
			mGameContext.popUpStack.addMessage(mGameContext.gameData.popUpMessage[2], mGameContext.gameData.popUpButton[2]);

			changeCurrentCloud(failureId);
			resetAll();
		}
		else
		{
			//Success
			mGameContext.popUpStack.addMessage(mGameContext.gameData.popUpMessage[0], mGameContext.gameData.popUpButton[0]);

			mGameContext.dataReader.writeLevelStatus(mGameContext.levelData.world, mGameContext.levelData.level, Enums::eLevelStatus::Complete);
		}
	}

	//TODO Use the report to clear level
}

bool Level::saveBoard()
{
	return mGameContext.dataReader.writeSavedBoard(mGameContext.levelData.world, mGameContext.levelData.level, mBoard.convertToString());
}

void Level::handleEventCurrent(const sf::Event & event)
{
	//TODO All events for tests purposes only
	switch (event.type)
	{
	case sf::Event::MouseButtonReleased:
		if (mDebugMode && event.mouseButton.button == sf::Mouse::Button::Left)
		{
			float i = (event.mouseButton.x - mCanvas.getTopLeftCorner().x) * mCanvas.getWidth() / mCanvas.getBoundingBox().x;
			float j = (event.mouseButton.y - mCanvas.getTopLeftCorner().y) * mCanvas.getHeight() / mCanvas.getBoundingBox().y;

			if (i >= 0.0f && i < mCanvas.getWidth() && j >= 0.0f && j < mCanvas.getHeight())
			{
				mCanvas.get(static_cast<unsigned int>(i), static_cast<unsigned int>(j)).setIsCloud(true);
			}
		}
		else if (mDebugMode && event.mouseButton.button == sf::Mouse::Button::Right)
		{
			float i = (event.mouseButton.x - mCanvas.getTopLeftCorner().x) * mCanvas.getWidth() / mCanvas.getBoundingBox().x;
			float j = (event.mouseButton.y - mCanvas.getTopLeftCorner().y) * mCanvas.getHeight() / mCanvas.getBoundingBox().y;

			if (i >= 0.0f && i < mCanvas.getWidth() && j >= 0.0f && j < mCanvas.getHeight())
			{
				mCanvas.get(static_cast<unsigned int>(i), static_cast<unsigned int>(j)).setIsCloud(false);
			}
		}
		break;
	case sf::Event::KeyReleased:
		if (mDebugMode && event.key.code == sf::Keyboard::B)
		{
			std::cout << "Board code : " + mBoard.convertToString() << std::endl;
		}
		else if (mDebugMode && event.key.code == sf::Keyboard::C)
		{
			std::cout << "Canvas code : " + mCanvas.convertToString() << std::endl;
		}
		else if (mDebugMode && event.key.code == sf::Keyboard::Numpad1)
		{
			mCanvas.removeColumn();
			setPositionChilds(mTopLeftCorner, mBoundingBox);
		}
		else if (mDebugMode && event.key.code == sf::Keyboard::Numpad2)
		{
			mCanvas.addColumn();
			setPositionChilds(mTopLeftCorner, mBoundingBox);
		}
		else if (mDebugMode && event.key.code == sf::Keyboard::Numpad9)
		{
			mCanvas.removeRow();
			setPositionChilds(mTopLeftCorner, mBoundingBox);
		}
		else if (mDebugMode && event.key.code == sf::Keyboard::Numpad6)
		{
			mCanvas.addRow();
			setPositionChilds(mTopLeftCorner, mBoundingBox);
		}
		break;
	}
}

void Level::updateCurrent(sf::Time dt)
{
	if (mBoard.hasUpdatedStartPoints()) //Note : can only happen in build mode
	{
		mRobots.startPointsUpdated();
	}
}

void Level::setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	mCanvas.setPositionAll(minCorner, sf::Vector2f(maxBox.x / 2.0f, maxBox.y * 3.0f / 4.0f));
	mBoard.setPositionAll(sf::Vector2f(minCorner.x + maxBox.x / 2.0f, minCorner.y), sf::Vector2f(maxBox.x / 2.0f, maxBox.y * 3.0f / 4.0f));
	mMenu.setPositionAll(sf::Vector2f(minCorner.x, minCorner.y + maxBox.y * 3.0f / 4.0f), sf::Vector2f(maxBox.x, maxBox.y / 4.0f));
	mInstructionDragger.setPositionAll(minCorner, maxBox);
	mPlayer.setPositionAll(minCorner, maxBox);

	mRobots.setPositionAll(minCorner, maxBox);
}

void Level::updateChildsVector()
{
	mChilds.clear();
	mChilds.push_back(mCanvas);
	mChilds.push_back(mBoard);

	mChilds.push_back(mRobots);

	mChilds.push_back(mMenu);
	mChilds.push_back(mInstructionDragger);
	mChilds.push_back(mPlayer);
}

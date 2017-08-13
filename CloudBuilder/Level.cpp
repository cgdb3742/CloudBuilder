#include <iostream>
#include "Level.h"



Level::Level():
	mCanvas(10, 10),
	mBoard(8, 8),
	mIsRunning(false),
	mPlayer(*this, mRobots),
	mMenu(mBoard, mPlayer),
	mInstructionDragger(mBoard, mMenu.getCreator())
{
	std::cout << "Creating GameEntity : Level." << std::endl;
	createRobotPairs(1);
	//mMenu.changeSelection(0);

	std::cout << mCanvas.convertToString() << std::endl;
}

Level::Level(unsigned int nbRobots) :
	mCanvas(10, 10),
	mBoard(8, 8),
	mIsRunning(false),
	mPlayer(*this, mRobots),
	mMenu(mBoard, mPlayer),
	mInstructionDragger(mBoard, mMenu.getCreator())
{
	std::cout << "Creating GameEntity : Level." << std::endl;
	createRobotPairs(nbRobots);
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

		mRobots.insert(std::pair<Enums::eColor, RobotPair>(color, RobotPair(mCanvas, mBoard, color)));
		//mRobots.push_back(RobotPair(mCanvas, mBoard, color));
		//mRobots.push_back(RobotPair(mCanvas, mBoard, Enums::eColor::Yellow));
	}
}

bool Level::createStartInstructionSpace(unsigned int i, unsigned int j, Enums::eColor color)
{
	
	return false;
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

void Level::resetAll()
{
	for (auto& pair : mRobots)
	{
		pair.second.resetAll();
	}

	//TODO Reset CloudBoard
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

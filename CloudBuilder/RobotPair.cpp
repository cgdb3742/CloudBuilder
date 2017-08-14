#include <iostream>
#include <utility>
#include "RobotPair.h"



RobotPair::RobotPair(GameContext& gameContext, CloudCanvas& canvas, InstructionBoard& board):
	GameEntity(gameContext),
	mColor(Enums::eColor::NoColor),
	mCloudRobot(gameContext, canvas),
	mInstructionRobot(gameContext, board),
	mCanvas(canvas),
	mBoard(board),
	mInstructionDone(false)
{
	std::cout << "Creating GameEntity : RobotPair." << std::endl;

	std::pair<unsigned int, unsigned int> startPos = board.getStartPosition(mColor);
	mInstructionRobot.setPos(startPos.first, startPos.second);
}

RobotPair::RobotPair(GameContext& gameContext, CloudCanvas& canvas, InstructionBoard& board, Enums::eColor color) :
	GameEntity(gameContext),
	mColor(color),
	mCloudRobot(gameContext, canvas, color),
	mInstructionRobot(gameContext, board, color),
	mCanvas(canvas),
	mBoard(board),
	mInstructionDone(false)
{
	std::cout << "Creating GameEntity : RobotPair." << std::endl;

	std::pair<unsigned int, unsigned int> startPos = board.getStartPosition(color);
	mInstructionRobot.setPos(startPos.first, startPos.second);
}


RobotPair::~RobotPair()
{
}

void RobotPair::startPointsUpdated() //Only called in build mode
{
	std::pair<unsigned int, unsigned int> startPos = mBoard.getStartPosition(mColor);
	if (mInstructionRobot.setPos(startPos.first, startPos.second))
	{
		InstructionSquare& currentInstruction = mInstructionRobot.getPos();
		mInstructionRobot.setPositionAll(currentInstruction.getTopLeftCorner(), currentInstruction.getBoundingBox());
	}
}

void RobotPair::resetInstructionDone()
{
	mInstructionDone = false;
}

bool RobotPair::applyInstruction(float progress)
{
	if (mInstructionDone)
	{
		return true;
	}

	mInstructionDone = (mInstructionRobot.getPos()).applyInstruction(mCloudRobot, mCanvas, mInstructionRobot, progress);
	
	setPositionChilds(mTopLeftCorner, mBoundingBox);//TODO Can do better
	
	return mInstructionDone;
}

bool RobotPair::moveInstructionRobot(float progress) //TODO Should always return true for progress >= 1.0f
{
	//std::cout << "Almost moving Instruction Robot " << mColor << std::endl;

	if (mInstructionDone)
	{
		return true;
	}

	//std::cout << "Moving Instruction Robot " << mColor << std::endl;

	switch (mInstructionRobot.getPos().getNextDir(mInstructionRobot))
	{
	case Enums::eDir::Center: mInstructionDone = true; break;
	case Enums::eDir::Right: mInstructionDone = mInstructionRobot.moveRight(progress); break;
	case Enums::eDir::Up: mInstructionDone = mInstructionRobot.moveUp(progress); break;
	case Enums::eDir::Left: mInstructionDone = mInstructionRobot.moveLeft(progress); break;
	case Enums::eDir::Down: mInstructionDone = mInstructionRobot.moveDown(progress); break;
	default: mInstructionDone = true; break;
	}

	setPositionChilds(mTopLeftCorner, mBoundingBox);//TODO Can do better

	return mInstructionDone;
}

void RobotPair::resetAll()
{
	mInstructionDone = false;
	mInstructionRobot.resetAll();
	mCloudRobot.resetAll();
	setPositionChilds(mTopLeftCorner, mBoundingBox);
}

Enums::eResult RobotPair::getResult()
{
	return mInstructionRobot.getResult();
}

CloudRobot & RobotPair::getCloudRobot()
{
	return mCloudRobot;
}

InstructionRobot & RobotPair::getInstructionRobot()
{
	return mInstructionRobot;
}

void RobotPair::setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	//std::cout << "Setting Position RobotPair " << mColor << std::endl;
	CloudSquare& currentCloud = mCloudRobot.getPos();
	mCloudRobot.setPositionAll(currentCloud.getTopLeftCorner(), currentCloud.getBoundingBox());
	InstructionSquare& currentInstruction = mInstructionRobot.getPos();
	mInstructionRobot.setPositionAll(currentInstruction.getTopLeftCorner(), currentInstruction.getBoundingBox());
}

void RobotPair::updateChildsVector()
{
	mChilds.clear();
	mChilds.push_back(mCloudRobot);
	mChilds.push_back(mInstructionRobot);
}

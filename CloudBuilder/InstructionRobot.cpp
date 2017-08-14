#include <iostream>
#include "InstructionRobot.h"



InstructionRobot::InstructionRobot(GameContext& gameContext, InstructionBoard& board):
	GameEntity(gameContext),
	mBoard(board),
	mPosi(0),
	mPosj(0),
	mColor(Enums::eColor::NoColor),
	mLastCheck(false),
	mPosOffset(sf::Vector2f(0.0f,0.0f)),
	mResult(Enums::eResult::Running)
{
	std::cout << "Creating GameEntity : InstructionRobot." << std::endl;
}

InstructionRobot::InstructionRobot(GameContext& gameContext, InstructionBoard & board, Enums::eColor color) :
	GameEntity(gameContext),
	mBoard(board),
	mPosi(0),
	mPosj(0),
	mColor(color),
	mLastCheck(false),
	mPosOffset(sf::Vector2f(0.0f, 0.0f)),
	mResult(Enums::eResult::Running)
{
}


InstructionRobot::~InstructionRobot()
{
}

InstructionSquare & InstructionRobot::getPos()
{
	return mBoard.get(mPosi, mPosj);
}

bool InstructionRobot::setPos(unsigned int i, unsigned int j)
{
	if (mBoard.exists(i, j))
	{
		mPosi = i;
		mPosj = j;
		return true;
	}
	else
	{
		return false;//If trying to move to a non-existant position, just stay there
	}
}

bool InstructionRobot::move(unsigned int i, unsigned int j, float progress)
{
	if (mBoard.exists(i, j))
	{
		if (progress >= 1.0f)
		{
			mPosOffset = sf::Vector2f(0.0f, 0.0f);
			mPosi = i;
			mPosj = j;
			return true;
		}
		else
		{
			mPosOffset = (mBoard.get(i, j).getTopLeftCorner() - mBoard.get(mPosi, mPosj).getTopLeftCorner()) * progress;
			return false;
		}
	}
	else
	{
		return true;//If trying to move to a non-existant position, just stay there
	}
}

bool InstructionRobot::moveLeft(float progress)
{
	return move(mPosi - 1, mPosj, progress);
}

bool InstructionRobot::moveRight(float progress)
{
	return move(mPosi + 1, mPosj, progress);
}

bool InstructionRobot::moveUp(float progress)
{
	return move(mPosi, mPosj - 1, progress);
}

bool InstructionRobot::moveDown(float progress)
{
	return move(mPosi, mPosj + 1, progress);
}

void InstructionRobot::resetAll()
{
	setPos(mBoard.getStartPosition(mColor).first, mBoard.getStartPosition(mColor).second);
	mPosOffset = sf::Vector2f(0.0f, 0.0f);
}

bool InstructionRobot::getLastCheck()
{
	return mLastCheck;
}

void InstructionRobot::setLastCheck(bool newValue)
{
	mLastCheck = newValue;
}

Enums::eResult InstructionRobot::getResult()
{
	return mResult;
}

void InstructionRobot::setResult(Enums::eResult newValue)
{
	mResult = newValue;
}

bool InstructionRobot::getIsActive()
{
	return mIsActive;
}

void InstructionRobot::setIsActive(bool newValue)
{
	mIsActive = newValue;
}

void InstructionRobot::drawCurrent(sf::RenderTarget & target)
{
	if (mColor == Enums::eColor::NoColor)
	{
		return;
	}

	sf::RectangleShape border(sf::Vector2f(0.5f*mBoundingBox.x, 0.2f*mBoundingBox.y));
	sf::RectangleShape nonBorder(sf::Vector2f(0.2f*mBoundingBox.x, 0.3f*mBoundingBox.y));

	switch (mColor)
	{
	case Enums::eColor::Red:
		nonBorder.setPosition(sf::Vector2f(0.0f*mBoundingBox.x, 0.2f*mBoundingBox.y));
		break;
	case Enums::eColor::Blue:
		border.setPosition(sf::Vector2f(0.5f*mBoundingBox.x, 0.0f*mBoundingBox.y));
		nonBorder.setPosition(sf::Vector2f(0.8f*mBoundingBox.x, 0.2f*mBoundingBox.y));
		break;
	case Enums::eColor::Green:
		border.setPosition(sf::Vector2f(0.0f*mBoundingBox.x, 0.8f*mBoundingBox.y));
		nonBorder.setPosition(sf::Vector2f(0.0f*mBoundingBox.x, 0.5f*mBoundingBox.y));
		break;
	case Enums::eColor::Yellow:
		border.setPosition(sf::Vector2f(0.5f*mBoundingBox.x, 0.8f*mBoundingBox.y));
		nonBorder.setPosition(sf::Vector2f(0.8f*mBoundingBox.x, 0.5f*mBoundingBox.y));
		break;
	}

	sf::Color drawColor = Enums::getColor(mColor);
	drawColor.a = 191;
	if (drawColor.r == 0)
	{
		drawColor.r = 63;
	}
	if (drawColor.g == 0)
	{
		drawColor.g = 63;
	}
	if (drawColor.b == 0)
	{
		drawColor.b = 63;
	}

	border.setFillColor(drawColor);
	//border.scale(mBoundingBox);
	border.move(mTopLeftCorner);
	nonBorder.setFillColor(drawColor);
	//nonBorder.scale(mBoundingBox);
	nonBorder.move(mTopLeftCorner);
	target.draw(border);
	target.draw(nonBorder);
}

void InstructionRobot::setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	//std::cout << "Setting Position InstructionRobot " << mColor << std::endl;
	mTopLeftCorner = minCorner + mPosOffset;
	mBoundingBox = maxBox;
}

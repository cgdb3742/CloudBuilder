#include <iostream>
#include "CloudRobot.h"



CloudRobot::CloudRobot(GameContext& gameContext, CloudCanvas& canvas):
	GameEntity(gameContext),
	mCanvas(canvas),
	mPosi(0),
	mPosj(0),
	mIsWriter(false),
	mColor(Enums::eColor::NoColor)
{
	std::cout << "Creating GameEntity : CloudRobot." << std::endl;
}

CloudRobot::CloudRobot(GameContext& gameContext, CloudCanvas & canvas, bool isWriter) :
	GameEntity(gameContext),
	mCanvas(canvas),
	mPosi(0),
	mPosj(0),
	mIsWriter(isWriter),
	mColor(Enums::eColor::NoColor)
{
	std::cout << "Creating GameEntity : CloudRobot." << std::endl;
}

CloudRobot::CloudRobot(GameContext& gameContext, CloudCanvas & canvas, Enums::eColor color) :
	GameEntity(gameContext),
	mCanvas(canvas),
	mPosi(0),
	mPosj(0),
	mIsWriter(false),
	mColor(color)
{
}

CloudRobot::CloudRobot(GameContext& gameContext, CloudCanvas & canvas, Enums::eColor color, bool isWriter) :
	GameEntity(gameContext),
	mCanvas(canvas),
	mPosi(0),
	mPosj(0),
	mIsWriter(isWriter),
	mColor(color)
{
}


CloudRobot::~CloudRobot()
{
}

bool CloudRobot::getIsWriter()
{
	return mIsWriter;
}

void CloudRobot::setIsWriter(bool newValue)
{
	mIsWriter = newValue;
}

CloudSquare & CloudRobot::getPos()
{
	return mCanvas.get(mPosi, mPosj);
}

unsigned int CloudRobot::getPosi()
{
	return mPosi;
}

unsigned int CloudRobot::getPosj()
{
	return mPosj;
}

bool CloudRobot::setPos(unsigned int i, unsigned int j)
{
	if (mCanvas.exists(i, j))
	{
		mPosi = i;
		mPosj = j;
		return true;
	}
	else
	{
		return true;//If trying to move to a non-existant position, just stay there
	}
}

bool CloudRobot::move(unsigned int i, unsigned int j, float progress)
{
	if (mCanvas.exists(i, j))
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
			mPosOffset = (mCanvas.get(i, j).getTopLeftCorner() - mCanvas.get(mPosi, mPosj).getTopLeftCorner()) * progress;
			return false;
		}
	}
	else
	{
		return true;//If trying to move to a non-existant position, just stay there
	}
}

bool CloudRobot::moveLeft(float progress)
{
	return move(mPosi - 1, mPosj, progress);
}

bool CloudRobot::moveRight(float progress)
{
	return move(mPosi + 1, mPosj, progress);
}

bool CloudRobot::moveUp(float progress)
{
	return move(mPosi, mPosj - 1, progress);
}

bool CloudRobot::moveDown(float progress)
{
	return move(mPosi, mPosj + 1, progress);
}

void CloudRobot::resetAll()
{
	setPos(0, 0);
	mPosOffset = sf::Vector2f(0.0f, 0.0f);
}

void CloudRobot::drawCurrent(sf::RenderTarget & target)
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

void CloudRobot::setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	mTopLeftCorner = minCorner + mPosOffset;
	mBoundingBox = maxBox;
}

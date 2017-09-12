#include <iostream>
#include "InstructionRobot.h"
#include "Game.h"



InstructionRobot::InstructionRobot(GameContext& gameContext, InstructionBoard& board, bool isVisible) :
	GameEntity(gameContext),
	mBoard(board),
	mPosi(0),
	mPosj(0),
	mColor(Enums::eColor::NoColor),
	mLastCheck(false),
	mPosOffset(sf::Vector2f(0.0f, 0.0f)),
	mResult(Enums::eResult::Running),
	mRotation(0.0f),
	mMaxRotation(15.0f),
	mRotateLeft(false),
	mIsVisible(isVisible)
{
	std::cout << "Creating GameEntity : InstructionRobot." << std::endl;

	mHead = gameContext.resourceHandler.createSprite(SpriteHandler::eSprite::Head);
	mFace = gameContext.resourceHandler.createSprite(SpriteHandler::eSprite::FaceNeutral);

	sf::FloatRect headRect = mHead.getLocalBounds();
	mHead.setOrigin(headRect.left + headRect.width / 2.0f, headRect.top + headRect.height / 2.0f);
	sf::FloatRect faceRect = mFace.getLocalBounds();
	mFace.setOrigin(faceRect.left + faceRect.width / 2.0f, faceRect.top + faceRect.height / 2.0f);
}

InstructionRobot::InstructionRobot(GameContext& gameContext, InstructionBoard & board, Enums::eColor color, bool isVisible) :
	GameEntity(gameContext),
	mBoard(board),
	mPosi(0),
	mPosj(0),
	mColor(color),
	mLastCheck(false),
	mPosOffset(sf::Vector2f(0.0f, 0.0f)),
	mResult(Enums::eResult::Running),
	mRotation(0.0f),
	mMaxRotation(15.0f),
	mRotateLeft(false),
	mIsVisible(isVisible)
{
	std::cout << "Creating GameEntity : InstructionRobot." << std::endl;

	mHead = gameContext.resourceHandler.createSprite(SpriteHandler::eSprite::Head);
	mFace = gameContext.resourceHandler.createSprite(SpriteHandler::eSprite::FaceNeutral);

	switch (color)
	{
	case Enums::eColor::Red: mBand = gameContext.resourceHandler.createSprite(SpriteHandler::eSprite::BandRed); break;
	case Enums::eColor::Blue: mBand = gameContext.resourceHandler.createSprite(SpriteHandler::eSprite::BandBlue); break;
	case Enums::eColor::Green: mBand = gameContext.resourceHandler.createSprite(SpriteHandler::eSprite::BandGreen); break;
	case Enums::eColor::Yellow: mBand = gameContext.resourceHandler.createSprite(SpriteHandler::eSprite::BandYellow); break;
	}


	sf::FloatRect headRect = mHead.getLocalBounds();
	mHead.setOrigin(headRect.left + headRect.width / 2.0f, headRect.top + headRect.height / 2.0f);
	sf::FloatRect faceRect = mFace.getLocalBounds();
	mFace.setOrigin(faceRect.left + faceRect.width / 2.0f, faceRect.top + faceRect.height / 2.0f);

	if (color != Enums::eColor::NoColor)
	{
		sf::FloatRect bandRect = mBand.getLocalBounds();
		mBand.setOrigin(bandRect.left + bandRect.width / 2.0f, bandRect.top + bandRect.height / 2.0f);
	}
}


InstructionRobot::~InstructionRobot()
{
}

bool InstructionRobot::getIsVisible()
{
	return mIsVisible;
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
	setIsActive(true);
	mPosOffset = sf::Vector2f(0.0f, 0.0f);
	setResult(Enums::eResult::Running);
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
	if (mIsVisible && mIsActive && !newValue)
	{
		changeFace(SpriteHandler::eSprite::FaceSleep);

		mRotation = 0.0f;
		mRotateLeft = false;
	}
	else if (mIsVisible && !mIsActive && newValue)
	{
		changeFace(SpriteHandler::eSprite::FaceNeutral);
	}

	mIsActive = newValue;
}

bool InstructionRobot::changeFace(SpriteHandler::eSprite newFace)
{
	if (newFace != SpriteHandler::eSprite::FaceAngry && newFace != SpriteHandler::eSprite::FaceHappy && newFace != SpriteHandler::eSprite::FaceNeutral && newFace != SpriteHandler::eSprite::FaceSleep)
	{
		return false;
	}

	mFace = mGameContext.resourceHandler.createSprite(newFace);

	sf::FloatRect faceRect = mFace.getLocalBounds();
	mFace.setOrigin(faceRect.left + faceRect.width / 2.0f, faceRect.top + faceRect.height / 2.0f);
	mFace.setScale(mBoundingBox / faceRect.height);
	mFace.setPosition(mTopLeftCorner);

	return true;
}

void InstructionRobot::updateCurrent(sf::Time dt)
{
	if (mIsActive)
	{
		float oldValue = mRotation;
		float rotate = mMaxRotation * dt.asSeconds() * 2.0f;

		if (mRotateLeft)
		{
			mRotation = std::max(mRotation - rotate, -mMaxRotation);
			mRotateLeft = !(mRotation <= -mMaxRotation);
		}
		else
		{
			mRotation = std::min(mRotation + rotate, mMaxRotation);
			mRotateLeft = (mRotation >= mMaxRotation);
		}
	}
}

void InstructionRobot::drawCurrent(sf::RenderTarget & target)
{
	if (mColor == Enums::eColor::NoColor)
	{
		return;
	}

	mHead.setRotation(mRotation);
	mFace.setRotation(mRotation);
	mBand.setRotation(mRotation);

	target.draw(mHead);
	target.draw(mFace);
	target.draw(mBand);

	//sf::RectangleShape border(sf::Vector2f(0.5f*mBoundingBox.x, 0.2f*mBoundingBox.y));
	//sf::RectangleShape nonBorder(sf::Vector2f(0.2f*mBoundingBox.x, 0.3f*mBoundingBox.y));

	//switch (mColor)
	//{
	//case Enums::eColor::Red:
	//	nonBorder.setPosition(sf::Vector2f(0.0f*mBoundingBox.x, 0.2f*mBoundingBox.y));
	//	break;
	//case Enums::eColor::Blue:
	//	border.setPosition(sf::Vector2f(0.5f*mBoundingBox.x, 0.0f*mBoundingBox.y));
	//	nonBorder.setPosition(sf::Vector2f(0.8f*mBoundingBox.x, 0.2f*mBoundingBox.y));
	//	break;
	//case Enums::eColor::Green:
	//	border.setPosition(sf::Vector2f(0.0f*mBoundingBox.x, 0.8f*mBoundingBox.y));
	//	nonBorder.setPosition(sf::Vector2f(0.0f*mBoundingBox.x, 0.5f*mBoundingBox.y));
	//	break;
	//case Enums::eColor::Yellow:
	//	border.setPosition(sf::Vector2f(0.5f*mBoundingBox.x, 0.8f*mBoundingBox.y));
	//	nonBorder.setPosition(sf::Vector2f(0.8f*mBoundingBox.x, 0.5f*mBoundingBox.y));
	//	break;
	//}

	//sf::Color drawColor = Enums::getColor(mColor);
	//drawColor.a = 191;
	//if (drawColor.r == 0)
	//{
	//	drawColor.r = 63;
	//}
	//if (drawColor.g == 0)
	//{
	//	drawColor.g = 63;
	//}
	//if (drawColor.b == 0)
	//{
	//	drawColor.b = 63;
	//}

	//if (!getIsActive())
	//{
	//	if (drawColor.r == 255)
	//	{
	//		drawColor.r = 127;
	//	}
	//	if (drawColor.g == 255)
	//	{
	//		drawColor.g = 127;
	//	}
	//	if (drawColor.b == 255)
	//	{
	//		drawColor.b = 127;
	//	}
	//}

	//border.setFillColor(drawColor);
	//border.move(mTopLeftCorner);
	//nonBorder.setFillColor(drawColor);
	//nonBorder.move(mTopLeftCorner);
	//target.draw(border);
	//target.draw(nonBorder);
}

void InstructionRobot::setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	sf::Vector2f colorOffset(maxBox / 4.0f);

	if (mColor == Enums::eColor::Blue || mColor == Enums::eColor::Yellow)
	{
		colorOffset.x += maxBox.x / 2.0f;
	}
	if (mColor == Enums::eColor::Green || mColor == Enums::eColor::Yellow)
	{
		colorOffset.y += maxBox.y / 2.0f;
	}

	//std::cout << "Setting Position InstructionRobot " << mColor << std::endl;
	mTopLeftCorner = minCorner + mPosOffset + colorOffset;
	mBoundingBox = maxBox / 2.0f;

	mHead.setScale(mBoundingBox / mHead.getLocalBounds().height);
	mFace.setScale(mBoundingBox / mFace.getLocalBounds().height);
	mBand.setScale(mBoundingBox / mBand.getLocalBounds().height);

	mHead.setPosition(mTopLeftCorner);
	mFace.setPosition(mTopLeftCorner);
	mBand.setPosition(mTopLeftCorner);
}

#include <iostream>
#include "CloudRobot.h"
#include "Game.h"



CloudRobot::CloudRobot(GameContext& gameContext, CloudCanvas& canvas, bool isVisible) :
	GameEntity(gameContext),
	mCanvas(canvas),
	mPosi(0),
	mPosj(0),
	mIsWriter(false),
	mIsVisible(isVisible),
	mColor(Enums::eColor::NoColor),
	mBodyRotation(0.0f),
	mBackArmRotation(0.0f),
	mFrontArmRotation(0.0f),
	mBackLegRotation(0.0f),
	mFrontLegRotation(0.0f),
	mFlyUp(false),
	mFlyOffset(0.0f),
	mFlyMax(0.1f)
{
	std::cout << "Creating GameEntity : CloudRobot." << std::endl;

	loadSprites();
}

CloudRobot::CloudRobot(GameContext& gameContext, CloudCanvas & canvas, bool isWriter, bool isVisible) :
	GameEntity(gameContext),
	mCanvas(canvas),
	mPosi(0),
	mPosj(0),
	mIsWriter(isWriter),
	mIsVisible(isVisible),
	mColor(Enums::eColor::NoColor),
	mBodyRotation(0.0f),
	mBackArmRotation(0.0f),
	mFrontArmRotation(0.0f),
	mBackLegRotation(0.0f),
	mFrontLegRotation(0.0f),
	mFlyUp(false),
	mFlyOffset(0.0f),
	mFlyMax(0.1f)
{
	std::cout << "Creating GameEntity : CloudRobot." << std::endl;

	loadSprites();
}

CloudRobot::CloudRobot(GameContext& gameContext, CloudCanvas & canvas, Enums::eColor color, bool isVisible) :
	GameEntity(gameContext),
	mCanvas(canvas),
	mPosi(0),
	mPosj(0),
	mIsWriter(false),
	mIsVisible(isVisible),
	mColor(color),
	mBodyRotation(0.0f),
	mBackArmRotation(0.0f),
	mFrontArmRotation(0.0f),
	mBackLegRotation(0.0f),
	mFrontLegRotation(0.0f),
	mFlyUp(false),
	mFlyOffset(0.0f),
	mFlyMax(0.1f)
{
	loadSprites();
}

CloudRobot::CloudRobot(GameContext& gameContext, CloudCanvas & canvas, Enums::eColor color, bool isWriter, bool isVisible) :
	GameEntity(gameContext),
	mCanvas(canvas),
	mPosi(0),
	mPosj(0),
	mIsWriter(isWriter),
	mIsVisible(isVisible),
	mColor(color),
	mBodyRotation(0.0f),
	mBackArmRotation(0.0f),
	mFrontArmRotation(0.0f),
	mBackLegRotation(0.0f),
	mFrontLegRotation(0.0f),
	mFlyUp(false),
	mFlyOffset(0.0f),
	mFlyMax(0.1f)
{
	loadSprites();
}


CloudRobot::~CloudRobot()
{
}

bool CloudRobot::getIsVisible()
{
	return mIsVisible;
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

	animateBody(20.0f, 0.0f, 0.0f, 0.0f, 0.0f, true);

	//mFlyUp = false;
	//mFlyOffset = 0.0f;
}

void CloudRobot::animateBody(float bodyRotation, float backArmRotation, float frontArmRotation, float backLegRotation, float frontLegRotation, bool reflect)
{
	float reflectRatio = (!reflect || mColor == Enums::eColor::Red || mColor == Enums::eColor::Green) ? 1.0f : -1.0f;

	mBodyRotation = bodyRotation * reflectRatio;

	animateBody(backArmRotation, frontArmRotation, backLegRotation, frontLegRotation, reflect);
}

void CloudRobot::animateBody(float backArmRotation, float frontArmRotation, float backLegRotation, float frontLegRotation, bool reflect)
{
	float reflectRatio = (!reflect || mColor == Enums::eColor::Red || mColor == Enums::eColor::Green) ? 1.0f : -1.0f;
	float side = (mColor == Enums::eColor::Red || mColor == Enums::eColor::Green) ? 1.0f : -1.0f;

	mBackArmRotation = backArmRotation * reflectRatio;
	mFrontArmRotation = frontArmRotation * reflectRatio;
	mBackLegRotation = backLegRotation * reflectRatio;
	mFrontLegRotation = frontLegRotation * reflectRatio;

	mBody.setPosition(mTopLeftCorner);
	mShirt.setPosition(mTopLeftCorner);

	mBody.setRotation(mBodyRotation);
	mShirt.setRotation(mBodyRotation);

	sf::Vector2f backArmPos(0.05f * side * mBoundingBox.x, -0.12f * mBoundingBox.y);
	sf::Vector2f frontArmPos(-0.05f * side * mBoundingBox.x, -0.12f * mBoundingBox.y);
	sf::Vector2f backLegPos(0.05f * side * mBoundingBox.x, 0.14f *mBoundingBox.y);
	sf::Vector2f frontLegPos(-0.05f * side * mBoundingBox.x, 0.14f * mBoundingBox.y);

	sf::Transform bodyRotation = sf::Transform::Identity;
	bodyRotation.rotate(mBodyRotation);

	mBackArm.setPosition(mTopLeftCorner + bodyRotation * backArmPos);
	mFrontArm.setPosition(mTopLeftCorner + bodyRotation * frontArmPos);
	mBackLeg.setPosition(mTopLeftCorner + bodyRotation * backLegPos);
	mFrontLeg.setPosition(mTopLeftCorner + bodyRotation * frontLegPos);

	mBackArm.setRotation(mBackArmRotation);
	mFrontArm.setRotation(mFrontArmRotation);
	mBackLeg.setRotation(mBackLegRotation);
	mFrontLeg.setRotation(mFrontLegRotation);

	mBody.move(0.0f, mFlyOffset * mBoundingBox.y);
	mShirt.move(0.0f, mFlyOffset * mBoundingBox.y);
	mBackArm.move(0.0f, mFlyOffset * mBoundingBox.y);
	mBackLeg.move(0.0f, mFlyOffset * mBoundingBox.y);
	mFrontArm.move(0.0f, mFlyOffset * mBoundingBox.y);
	mFrontLeg.move(0.0f, mFlyOffset * mBoundingBox.y);
}

void CloudRobot::updateCurrent(sf::Time dt)
{
	float oldValue = mFlyOffset;
	float flyDist = mFlyMax * dt.asSeconds() * 0.5f;

	if (mFlyUp)
	{
		mFlyOffset = std::max(mFlyOffset - flyDist, -mFlyMax);
		mFlyUp = !(mFlyOffset <= -mFlyMax);

		mBody.move(0.0f, (mFlyOffset - oldValue) * mBoundingBox.y);
		mShirt.move(0.0f, (mFlyOffset - oldValue) * mBoundingBox.y);
		mBackArm.move(0.0f, (mFlyOffset - oldValue) * mBoundingBox.y);
		mBackLeg.move(0.0f, (mFlyOffset - oldValue) * mBoundingBox.y);
		mFrontArm.move(0.0f, (mFlyOffset - oldValue) * mBoundingBox.y);
		mFrontLeg.move(0.0f, (mFlyOffset - oldValue) * mBoundingBox.y);
	}
	else
	{
		mFlyOffset = std::min(mFlyOffset + flyDist, mFlyMax);
		mFlyUp = (mFlyOffset >= mFlyMax);

		mBody.move(0.0f, (mFlyOffset - oldValue) * mBoundingBox.y);
		mShirt.move(0.0f, (mFlyOffset - oldValue) * mBoundingBox.y);
		mBackArm.move(0.0f, (mFlyOffset - oldValue) * mBoundingBox.y);
		mBackLeg.move(0.0f, (mFlyOffset - oldValue) * mBoundingBox.y);
		mFrontArm.move(0.0f, (mFlyOffset - oldValue) * mBoundingBox.y);
		mFrontLeg.move(0.0f, (mFlyOffset - oldValue) * mBoundingBox.y);
	}
}

void CloudRobot::drawCurrent(sf::RenderTarget & target)
{
	if (mColor == Enums::eColor::NoColor)
	{
		return;
	}

	target.draw(mBackLeg);
	target.draw(mBackArm);
	target.draw(mBody);
	target.draw(mShirt);
	target.draw(mFrontLeg);
	target.draw(mFrontArm);

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

	//border.setFillColor(drawColor);
	//border.move(mTopLeftCorner);
	//nonBorder.setFillColor(drawColor);
	//nonBorder.move(mTopLeftCorner);
	//target.draw(border);
	//target.draw(nonBorder);
}

void CloudRobot::setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox)
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

	mTopLeftCorner = minCorner + mPosOffset + colorOffset;
	mBoundingBox = maxBox / 2.0f;

	float side = (mColor == Enums::eColor::Red || mColor == Enums::eColor::Green) ? 1.0f : -1.0f;

	mBody.setScale(mBoundingBox / (mBody.getLocalBounds().height * 2.0f));
	mShirt.setScale(mBoundingBox / (mShirt.getLocalBounds().height * 2.0f));
	mBackArm.setScale(mBoundingBox / (mBackArm.getLocalBounds().height * 2.0f));
	mFrontArm.setScale(mBoundingBox / (mFrontArm.getLocalBounds().height * 2.0f));
	mBackLeg.setScale(mBoundingBox / (mBackLeg.getLocalBounds().height * 2.0f));
	mFrontLeg.setScale(mBoundingBox / (mFrontLeg.getLocalBounds().height * 2.0f));

	animateBody(mBodyRotation, mBackArmRotation, mFrontArmRotation, mBackLegRotation, mFrontLegRotation, false);
}

void CloudRobot::loadSprites()
{
	float side = (mColor == Enums::eColor::Red || mColor == Enums::eColor::Green) ? 1.0f : -1.0f;
	mBodyRotation = 20.0f * side;

	mBody = mGameContext.resourceHandler.createSprite(SpriteHandler::eSprite::Body);
	mBackArm = mGameContext.resourceHandler.createSprite(SpriteHandler::eSprite::Limb);
	mFrontArm = mGameContext.resourceHandler.createSprite(SpriteHandler::eSprite::Limb);
	mBackLeg = mGameContext.resourceHandler.createSprite(SpriteHandler::eSprite::Limb);
	mFrontLeg = mGameContext.resourceHandler.createSprite(SpriteHandler::eSprite::Limb);

	switch (mColor)
	{
	case Enums::eColor::Red: mShirt = mGameContext.resourceHandler.createSprite(SpriteHandler::eSprite::ShirtRed); break;
	case Enums::eColor::Blue: mShirt = mGameContext.resourceHandler.createSprite(SpriteHandler::eSprite::ShirtBlue); break;
	case Enums::eColor::Green: mShirt = mGameContext.resourceHandler.createSprite(SpriteHandler::eSprite::ShirtGreen); break;
	case Enums::eColor::Yellow: mShirt = mGameContext.resourceHandler.createSprite(SpriteHandler::eSprite::ShirtYellow); break;
	}

	sf::FloatRect bodyRect = mBody.getLocalBounds();
	mBody.setOrigin(bodyRect.left + bodyRect.width / 2.0f, bodyRect.top + bodyRect.height / 2.0f);
	sf::FloatRect shirtRect = mShirt.getLocalBounds();
	mShirt.setOrigin(shirtRect.left + shirtRect.width / 2.0f, shirtRect.top + shirtRect.height / 2.0f);
	sf::FloatRect limbRect = mBackArm.getLocalBounds();
	mBackArm.setOrigin(limbRect.left + limbRect.width / 2.0f, limbRect.top + limbRect.height * 3.0f / 8.0f);
	mFrontArm.setOrigin(limbRect.left + limbRect.width / 2.0f, limbRect.top + limbRect.height * 3.0f / 8.0f);
	mBackLeg.setOrigin(limbRect.left + limbRect.width / 2.0f, limbRect.top + limbRect.height * 3.0f / 8.0f);
	mFrontLeg.setOrigin(limbRect.left + limbRect.width / 2.0f, limbRect.top + limbRect.height * 3.0f / 8.0f);
}

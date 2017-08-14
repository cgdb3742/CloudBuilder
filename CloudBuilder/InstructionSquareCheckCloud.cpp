#include "InstructionSquareCheckCloud.h"
#include "CloudRobot.h"
#include "InstructionRobot.h"



InstructionSquareCheckCloud::InstructionSquareCheckCloud(GameContext& gameContext) :
	InstructionSquare(gameContext, Enums::eInstruction::CheckCloud, "Check Cloud"),
	mNextTrue(Enums::eDir::Center),
	mNextFalse(Enums::eDir::Center),
	mCheckDir(Enums::eDir::Center),
	mRobotColor(Enums::eColor::NoColor),
	mWantCloud(true)
{
}

InstructionSquareCheckCloud::InstructionSquareCheckCloud(GameContext& gameContext, std::string & source) :
	InstructionSquare(gameContext, Enums::eInstruction::CheckCloud, "Check Cloud"),
	mNextTrue(Enums::eDir::Center),
	mNextFalse(Enums::eDir::Center),
	mCheckDir(Enums::eDir::Center),
	mRobotColor(Enums::eColor::NoColor),
	mWantCloud(true)
{
	convertFromString(source);
}


InstructionSquareCheckCloud::~InstructionSquareCheckCloud()
{
}

Enums::eDir InstructionSquareCheckCloud::getNextDir(InstructionRobot & robot)
{
	if (robot.getLastCheck())
	{
		return mNextTrue;
	}
	else
	{
		return mNextFalse;
	}
}

Enums::eDir InstructionSquareCheckCloud::getNextTrueDir()
{
	return mNextTrue;
}

void InstructionSquareCheckCloud::setNextTrueDir(Enums::eDir newDir)
{
	if (newDir == mNextFalse)
	{
		mNextFalse = mNextTrue;
	}
	
	mNextTrue = newDir;
}

Enums::eDir InstructionSquareCheckCloud::getNextFalseDir()
{
	return mNextFalse;
}

void InstructionSquareCheckCloud::setNextFalseDir(Enums::eDir newDir)
{
	if (newDir == mNextTrue)
	{
		mNextTrue = mNextFalse;
	}

	mNextFalse = newDir;
}

Enums::eDir InstructionSquareCheckCloud::getCheckDir()
{
	return mCheckDir;
}

void InstructionSquareCheckCloud::setCheckDir(Enums::eDir newDir)
{
	mCheckDir = newDir;
}

Enums::eColor InstructionSquareCheckCloud::getRobotColor()
{
	return mRobotColor;
}

void InstructionSquareCheckCloud::setRobotColor(Enums::eColor newColor)
{
	mRobotColor = newColor;
}

bool InstructionSquareCheckCloud::getWantCloud()
{
	return mWantCloud;
}

void InstructionSquareCheckCloud::setWantCloud(bool newWant)
{
	mWantCloud = newWant;
}

std::list<Enums::eInstructionModifier> InstructionSquareCheckCloud::getPossibleModifications()
{
	return { Enums::eInstructionModifier::NextDirTrue, Enums::eInstructionModifier::NextDirFalse, Enums::eInstructionModifier::CheckDir, Enums::eInstructionModifier::RobotColor, Enums::eInstructionModifier::CloudBool };
}

void InstructionSquareCheckCloud::applyModification(InstructionModificationData modificationData)
{
	switch (modificationData.modification)
	{
	case Enums::eInstructionModifier::NextDirTrue: setNextTrueDir(modificationData.dirData); break;
	case Enums::eInstructionModifier::NextDirFalse: setNextFalseDir(modificationData.dirData); break;
	case Enums::eInstructionModifier::CheckDir: setCheckDir(modificationData.dirData); break;
	case Enums::eInstructionModifier::RobotColor: setRobotColor(modificationData.colorData); break;
	case Enums::eInstructionModifier::CloudBool: setWantCloud(modificationData.boolData); break;
	default: InstructionSquare::applyModification(modificationData); break;
	}
}

std::string InstructionSquareCheckCloud::convertToString()
{
	return Enums::getString(getType()) + Enums::getString(getNextTrueDir()) + Enums::getString(getNextFalseDir()) + Enums::getString(getCheckDir()) + Enums::getString(getRobotColor()) + Enums::getString(getWantCloud());
}

bool InstructionSquareCheckCloud::convertFromString(std::string & source)
{
	if (source.substr(0, 2) == Enums::getString(getType()) && source.size() >= 7)
	{
		setNextTrueDir(Enums::getDirFromString(source[2]));
		setNextFalseDir(Enums::getDirFromString(source[3]));
		setCheckDir(Enums::getDirFromString(source[4]));
		setRobotColor(Enums::getColorFromString(source[5]));
		setWantCloud(Enums::getBoolFromString(source[6]));

		return true;
	}
	else
	{
		return false;
	}
}

bool InstructionSquareCheckCloud::applyInstruction(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, float progress)
{
	unsigned int toChecki = cloudRobot.getPosi();
	unsigned int toCheckj = cloudRobot.getPosj();

	switch (mCheckDir)
	{
	case Enums::eDir::Left: toChecki--; break;
	case Enums::eDir::Right: toChecki++; break;
	case Enums::eDir::Up: toCheckj--; break;
	case Enums::eDir::Down: toCheckj++; break;
	default: break;
	}

	instructionRobot.setLastCheck(canvas.getIsCloud(toChecki, toCheckj) == mWantCloud);

	//if (canvas.getIsCloud(toChecki, toCheckj) == mWantCloud)
	//{
	//	//setNextDir(mNextTrue);
	//}
	//else
	//{
	//	//setNextDir(mNextFalse);
	//}

	return true;
}

void InstructionSquareCheckCloud::setUpNextDir(bool isLeftBorder, bool isRightBorder, bool isUpBorder, bool isDownBorder)
{
	switch (mNextTrue)
	{
	case Enums::eDir::Center: mNextTrue = isRightBorder ? Enums::eDir::Left : Enums::eDir::Right; break;
	case Enums::eDir::Left: mNextTrue = isLeftBorder ? Enums::eDir::Right : Enums::eDir::Left; break;
	case Enums::eDir::Right: mNextTrue = isRightBorder ? Enums::eDir::Left : Enums::eDir::Right; break;
	case Enums::eDir::Up: mNextTrue = isUpBorder ? Enums::eDir::Down : Enums::eDir::Up; break;
	case Enums::eDir::Down: mNextTrue = isDownBorder ? Enums::eDir::Up : Enums::eDir::Down; break;
	}

	switch (mNextFalse)
	{
	case Enums::eDir::Center: mNextFalse = isRightBorder ? Enums::eDir::Left : Enums::eDir::Right; break;
	case Enums::eDir::Left: mNextFalse = isLeftBorder ? Enums::eDir::Right : Enums::eDir::Left; break;
	case Enums::eDir::Right: mNextFalse = isRightBorder ? Enums::eDir::Left : Enums::eDir::Right; break;
	case Enums::eDir::Up: mNextFalse = isUpBorder ? Enums::eDir::Down : Enums::eDir::Up; break;
	case Enums::eDir::Down: mNextFalse = isDownBorder ? Enums::eDir::Up : Enums::eDir::Down; break;
	}

	if (mNextTrue == mNextFalse) //TODO sub-optimal if mNextFalse correct and mNextTrue opposite and incorrect before placement ?
	{
		if (mNextTrue == Enums::eDir::Left || mNextTrue == Enums::eDir::Right)
		{
			mNextFalse = isDownBorder ? Enums::eDir::Up : Enums::eDir::Down;
		}
		else
		{
			mNextFalse = isRightBorder ? Enums::eDir::Left : Enums::eDir::Right;
		}
	}
}

void InstructionSquareCheckCloud::drawNextDir(sf::RenderTarget & target)
{
	if (mNextTrue != Enums::eDir::Center)
	{
		sf::ConvexShape arrow;
		arrow.setPointCount(4);

		switch (mNextTrue)
		{
		case Enums::eDir::Left:
			arrow.setPoint(0, sf::Vector2f(0.125f, 0.125f));
			arrow.setPoint(1, sf::Vector2f(0.0f, 0.5f));
			arrow.setPoint(2, sf::Vector2f(0.125f, 0.875f));
			arrow.setPoint(3, sf::Vector2f(0.0625f, 0.5f));
			break;
		case Enums::eDir::Right:
			arrow.setPoint(0, sf::Vector2f(0.875f, 0.125f));
			arrow.setPoint(1, sf::Vector2f(1.0f, 0.5f));
			arrow.setPoint(2, sf::Vector2f(0.875f, 0.875f));
			arrow.setPoint(3, sf::Vector2f(0.9375f, 0.5f));
			break;
		case Enums::eDir::Up:
			arrow.setPoint(0, sf::Vector2f(0.125f, 0.125f));
			arrow.setPoint(1, sf::Vector2f(0.5f, 0.0f));
			arrow.setPoint(2, sf::Vector2f(0.875f, 0.125f));
			arrow.setPoint(3, sf::Vector2f(0.5f, 0.0625f));
			break;
		case Enums::eDir::Down:
			arrow.setPoint(0, sf::Vector2f(0.125f, 0.875f));
			arrow.setPoint(1, sf::Vector2f(0.5f, 1.0f));
			arrow.setPoint(2, sf::Vector2f(0.875f, 0.875f));
			arrow.setPoint(3, sf::Vector2f(0.5f, 0.9375f));
			break;
		}
		arrow.setFillColor(sf::Color(0, 255, 0));
		arrow.setScale(mBoundingBox);
		arrow.setPosition(mTopLeftCorner);
		target.draw(arrow);
	}

	if (mNextFalse != Enums::eDir::Center)
	{
		sf::ConvexShape arrow;
		arrow.setPointCount(4);

		switch (mNextFalse)
		{
		case Enums::eDir::Left:
			arrow.setPoint(0, sf::Vector2f(0.125f, 0.125f));
			arrow.setPoint(1, sf::Vector2f(0.0f, 0.5f));
			arrow.setPoint(2, sf::Vector2f(0.125f, 0.875f));
			arrow.setPoint(3, sf::Vector2f(0.0625f, 0.5f));
			break;
		case Enums::eDir::Right:
			arrow.setPoint(0, sf::Vector2f(0.875f, 0.125f));
			arrow.setPoint(1, sf::Vector2f(1.0f, 0.5f));
			arrow.setPoint(2, sf::Vector2f(0.875f, 0.875f));
			arrow.setPoint(3, sf::Vector2f(0.9375f, 0.5f));
			break;
		case Enums::eDir::Up:
			arrow.setPoint(0, sf::Vector2f(0.125f, 0.125f));
			arrow.setPoint(1, sf::Vector2f(0.5f, 0.0f));
			arrow.setPoint(2, sf::Vector2f(0.875f, 0.125f));
			arrow.setPoint(3, sf::Vector2f(0.5f, 0.0625f));
			break;
		case Enums::eDir::Down:
			arrow.setPoint(0, sf::Vector2f(0.125f, 0.875f));
			arrow.setPoint(1, sf::Vector2f(0.5f, 1.0f));
			arrow.setPoint(2, sf::Vector2f(0.875f, 0.875f));
			arrow.setPoint(3, sf::Vector2f(0.5f, 0.9375f));
			break;
		}
		arrow.setFillColor(sf::Color(255, 0, 0));
		arrow.setScale(mBoundingBox);
		arrow.setPosition(mTopLeftCorner);
		target.draw(arrow);
	}
}

void InstructionSquareCheckCloud::drawInterior(sf::RenderTarget & target)
{
	sf::RectangleShape square(mBoundingBox*3.0f / 4.0f);
	square.setPosition(mTopLeftCorner + mBoundingBox / 8.0f);
	square.setFillColor(sf::Color(63, 63, 0));
	square.setOutlineThickness(1.0f);
	square.setOutlineColor(sf::Color(0, 0, 0));
	target.draw(square);

	sf::CircleShape robot(0.2f);
	robot.scale(mBoundingBox*3.0f / 4.0f);
	robot.move(sf::Vector2f(0.05f*mBoundingBox.x*3.0f / 4.0f, 0.55f*mBoundingBox.y*3.0f / 4.0f));
	robot.move(mTopLeftCorner + mBoundingBox / 8.0f);
	robot.setFillColor(Enums::getColor(mRobotColor));
	target.draw(robot);

	sf::ConvexShape direction;
	switch (mCheckDir)
	{
	case Enums::eDir::Left:
		direction.setPointCount(3);
		direction.setPoint(0, sf::Vector2f(0.4f, 0.0f));
		direction.setPoint(1, sf::Vector2f(0.4f, 0.4f));
		direction.setPoint(2, sf::Vector2f(0.0f, 0.2f));
		break;
	case Enums::eDir::Right:
		direction.setPointCount(3);
		direction.setPoint(0, sf::Vector2f(0.0f, 0.0f));
		direction.setPoint(1, sf::Vector2f(0.0f, 0.4f));
		direction.setPoint(2, sf::Vector2f(0.4f, 0.2f));
		break;
	case Enums::eDir::Up:
		direction.setPointCount(3);
		direction.setPoint(0, sf::Vector2f(0.0f, 0.4f));
		direction.setPoint(1, sf::Vector2f(0.4f, 0.4f));
		direction.setPoint(2, sf::Vector2f(0.2f, 0.0f));
		break;
	case Enums::eDir::Down:
		direction.setPointCount(3);
		direction.setPoint(0, sf::Vector2f(0.0f, 0.0f));
		direction.setPoint(1, sf::Vector2f(0.4f, 0.0f));
		direction.setPoint(2, sf::Vector2f(0.2f, 0.4f));
		break;
	case Enums::eDir::Center:
		direction.setPointCount(4);
		direction.setPoint(0, sf::Vector2f(0.0f, 0.2f));
		direction.setPoint(1, sf::Vector2f(0.2f, 0.0f));
		direction.setPoint(2, sf::Vector2f(0.4f, 0.2f));
		direction.setPoint(3, sf::Vector2f(0.2f, 0.4f));
		break;
	}
	direction.scale(mBoundingBox*3.0f / 4.0f);
	direction.move(sf::Vector2f(0.3f*mBoundingBox.x*3.0f / 4.0f, 0.05f*mBoundingBox.y*3.0f / 4.0f));
	direction.move(mTopLeftCorner + mBoundingBox / 8.0f);
	direction.setFillColor(sf::Color(127, 127, 127));
	target.draw(direction);

	sf::RectangleShape cloud(sf::Vector2f(0.4f,0.4f));
	cloud.scale(mBoundingBox*3.0f / 4.0f);
	cloud.move(sf::Vector2f(0.55f*mBoundingBox.x*3.0f / 4.0f, 0.55f*mBoundingBox.y*3.0f / 4.0f));
	cloud.move(mTopLeftCorner + mBoundingBox / 8.0f);
	if (mWantCloud)
	{
		cloud.setFillColor(sf::Color(255, 255, 255));
	}
	else
	{
		cloud.setFillColor(sf::Color(0, 0, 0));
	}
	target.draw(cloud);
}

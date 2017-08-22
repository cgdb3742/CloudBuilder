#include "InstructionSquareActCloud.h"
#include "CloudRobot.h"





InstructionSquareActCloud::InstructionSquareActCloud(GameContext & gameContext) :
	InstructionSquare(gameContext, Enums::eInstruction::ActSetCloud, "Cloud Action"),
	mWantCloud(true),
	mRobotColor(Enums::eColor::NoColor)
{
}

InstructionSquareActCloud::InstructionSquareActCloud(GameContext & gameContext, std::string & source) :
	InstructionSquare(gameContext, Enums::eInstruction::ActSetCloud, "Cloud Action"),
	mWantCloud(true),
	mRobotColor(Enums::eColor::NoColor)
{
	convertFromString(source);
}

InstructionSquareActCloud::~InstructionSquareActCloud()
{
}

bool InstructionSquareActCloud::getWantCloud()
{
	return mWantCloud;
}

void InstructionSquareActCloud::setWantCloud(bool newWant)
{
	mWantCloud = newWant;
}

Enums::eColor InstructionSquareActCloud::getRobotColor()
{
	return mRobotColor;
}

void InstructionSquareActCloud::setRobotColor(Enums::eColor newColor)
{
	mRobotColor = newColor;
}

std::list<Enums::eInstructionModifier> InstructionSquareActCloud::getPossibleModifications()
{
	return { Enums::eInstructionModifier::NextDir, Enums::eInstructionModifier::CloudBool, Enums::eInstructionModifier::RobotColor };
}

void InstructionSquareActCloud::applyModification(InstructionModificationData modificationData)
{
	switch (modificationData.modification)
	{
	case Enums::eInstructionModifier::NextDir: setNextDir(modificationData.dirData); break;
	case Enums::eInstructionModifier::CloudBool: setWantCloud(modificationData.boolData); break;
	case Enums::eInstructionModifier::RobotColor: setRobotColor(modificationData.colorData); break;
	default: InstructionSquare::applyModification(modificationData); break;
	}
}

std::string InstructionSquareActCloud::convertToString()
{
	return Enums::getString(getType()) + Enums::getString(getNextDir()) + Enums::getString(getWantCloud()) + Enums::getString(getRobotColor());
}

bool InstructionSquareActCloud::convertFromString(std::string & source)
{
	if (source.substr(0, 2) == Enums::getString(getType()) && source.size() >= 5)
	{
		setNextDir(Enums::getDirFromString(source[2]));
		setWantCloud(Enums::getBoolFromString(source[3]));
		setRobotColor(Enums::getColorFromString(source[4]));

		return true;
	}
	else
	{
		return false;
	}
}

bool InstructionSquareActCloud::applyInstruction(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, float progress)
{
	CloudRobot& actingRobot = cloudRobot; //TODO Control other robots

	if (!actingRobot.getIsWriter())
	{
		return true;
	}

	if (progress >= 1.0f)
	{
		actingRobot.getPos().setIsCloud(mWantCloud); //TODO Animation and concurrency between robots
		return true;
	}
	else
	{
		return false;
	}
}

void InstructionSquareActCloud::drawInterior(sf::RenderTarget & target)
{
	sf::RectangleShape square(mBoundingBox*3.0f / 4.0f);
	square.setPosition(mTopLeftCorner + mBoundingBox / 8.0f);
	square.setFillColor(sf::Color(0, 0, 63));
	square.setOutlineThickness(1.0f);
	square.setOutlineColor(sf::Color(0, 0, 0));
	target.draw(square);

	sf::CircleShape robot(0.2f);
	robot.scale(mBoundingBox*3.0f / 4.0f);
	robot.move(sf::Vector2f(0.05f*mBoundingBox.x*3.0f / 4.0f, 0.3f*mBoundingBox.y*3.0f / 4.0f));
	robot.move(mTopLeftCorner + mBoundingBox / 8.0f);
	robot.setFillColor(Enums::getColor(mRobotColor));
	target.draw(robot);

	sf::RectangleShape cloud(sf::Vector2f(0.4f, 0.4f));
	cloud.scale(mBoundingBox*3.0f / 4.0f);
	cloud.move(sf::Vector2f(0.55f*mBoundingBox.x*3.0f / 4.0f, 0.3f*mBoundingBox.y*3.0f / 4.0f));
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

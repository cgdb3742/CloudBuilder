#include "InstructionSquareActColor.h"
#include "CloudRobot.h"




InstructionSquareActColor::InstructionSquareActColor(GameContext & gameContext) :
	InstructionSquare(gameContext, Enums::eInstruction::ActSetColor, "Color Action"),
	mCloudColor(Enums::eColor::NoColor)
{
}

InstructionSquareActColor::InstructionSquareActColor(GameContext & gameContext, std::string & source) :
	InstructionSquare(gameContext, Enums::eInstruction::ActSetColor, "Color Action"),
	mCloudColor(Enums::eColor::NoColor)
{
	convertFromString(source);
}

InstructionSquareActColor::~InstructionSquareActColor()
{
}

bool InstructionSquareActColor::isValid()
{
	return InstructionSquare::isValid() && Enums::isValid(getRobotColor(), mGameContext);
}

Enums::eColor InstructionSquareActColor::getCloudColor()
{
	return mCloudColor;
}

void InstructionSquareActColor::setCloudColor(Enums::eColor newColor)
{
	mCloudColor = newColor;
}

std::list<Enums::eInstructionModifier> InstructionSquareActColor::getPossibleModifications()
{
	return { Enums::eInstructionModifier::NextDir, Enums::eInstructionModifier::CloudColor, Enums::eInstructionModifier::RobotColor };
}

void InstructionSquareActColor::applyModification(InstructionModificationData modificationData)
{
	switch (modificationData.modification)
	{
	case Enums::eInstructionModifier::NextDir: setNextDir(modificationData.dirData); break;
	case Enums::eInstructionModifier::CloudColor: setCloudColor(modificationData.colorData); break;
	case Enums::eInstructionModifier::RobotColor: setRobotColor(modificationData.colorData); break;
	default: InstructionSquare::applyModification(modificationData); break;
	}
}

std::string InstructionSquareActColor::convertToString()
{
	return Enums::getString(getType()) + Enums::getString(getNextDir()) + Enums::getString(getCloudColor()) + Enums::getString(getRobotColor());
}

bool InstructionSquareActColor::convertFromString(std::string & source)
{
	if (source.substr(0, 2) == Enums::getString(getType()) && source.size() >= 5)
	{
		setNextDir(Enums::getDirFromString(source[2]));
		setCloudColor(Enums::getColorFromString(source[3]));
		setRobotColor(Enums::getColorFromString(source[4]));

		return true;
	}
	else
	{
		return false;
	}
}

bool InstructionSquareActColor::applyInstruction(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, float progress)
{
	if (!cloudRobot.getIsWriter())
	{
		return true;
	}

	if (progress >= 1.0f)
	{
		cloudRobot.getPos().setColor(mCloudColor); //TODO Animation and concurrency between robots
		return true;
	}
	else
	{
		return false;
	}
}

void InstructionSquareActColor::drawInterior(sf::RenderTarget & target)
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
	cloud.setFillColor(Enums::getColor(mCloudColor));
	target.draw(cloud);
}

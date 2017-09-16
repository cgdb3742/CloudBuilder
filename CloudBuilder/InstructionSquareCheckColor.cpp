#include "InstructionSquareCheckColor.h"
#include "CloudRobot.h"
#include "InstructionRobot.h"





InstructionSquareCheckColor::InstructionSquareCheckColor(GameContext & gameContext) :
	InstructionSquareCheck(gameContext, Enums::eInstruction::CheckColor, "Check Color"),
	mCloudColor(Enums::eColor::NoColor)
{
}

InstructionSquareCheckColor::InstructionSquareCheckColor(GameContext & gameContext, std::wstring & source) :
	InstructionSquareCheck(gameContext, Enums::eInstruction::CheckColor, "Check Color"),
	mCloudColor(Enums::eColor::NoColor)
{
	convertFromString(source);
}

InstructionSquareCheckColor::~InstructionSquareCheckColor()
{
}

Enums::eColor InstructionSquareCheckColor::getCloudColor()
{
	return mCloudColor;
}

void InstructionSquareCheckColor::setCloudColor(Enums::eColor newColor)
{
	mCloudColor = newColor;
}

std::list<Enums::eInstructionModifier> InstructionSquareCheckColor::getPossibleModifications()
{
	return { Enums::eInstructionModifier::NextDirTrue, Enums::eInstructionModifier::NextDirFalse, Enums::eInstructionModifier::CheckDir, Enums::eInstructionModifier::RobotColor, Enums::eInstructionModifier::CloudColor };
}

void InstructionSquareCheckColor::applyModification(InstructionModificationData modificationData)
{
	switch (modificationData.modification)
	{
	case Enums::eInstructionModifier::CloudColor: setCloudColor(modificationData.colorData); break;
	default: InstructionSquareCheck::applyModification(modificationData); break;
	}
}

std::wstring InstructionSquareCheckColor::convertToString()
{
	return Enums::getString(getType()) + Enums::getString(getNextTrueDir()) + Enums::getString(getNextFalseDir()) + Enums::getString(getCheckDir()) + Enums::getString(getRobotColor()) + Enums::getString(getCloudColor());
}

bool InstructionSquareCheckColor::convertFromString(std::wstring & source)
{
	if (source.substr(0, 2) == Enums::getString(getType()) && source.size() >= 7)
	{
		setNextTrueDir(Enums::getDirFromString(source[2]));
		setNextFalseDir(Enums::getDirFromString(source[3]));
		setCheckDir(Enums::getDirFromString(source[4]));
		setRobotColor(Enums::getColorFromString(source[5]));
		setCloudColor(Enums::getColorFromString(source[6]));

		return true;
	}
	else
	{
		return false;
	}
}

bool InstructionSquareCheckColor::performCheck(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, unsigned int toChecki, unsigned int toCheckj)
{
	return (canvas.getColor(toChecki, toCheckj) == mCloudColor);
}

void InstructionSquareCheckColor::drawInterior(sf::RenderTarget & target)
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

	sf::RectangleShape cloud(sf::Vector2f(0.4f, 0.4f));
	cloud.scale(mBoundingBox*3.0f / 4.0f);
	cloud.move(sf::Vector2f(0.55f*mBoundingBox.x*3.0f / 4.0f, 0.55f*mBoundingBox.y*3.0f / 4.0f));
	cloud.move(mTopLeftCorner + mBoundingBox / 8.0f);
	cloud.setFillColor(Enums::getColor(mCloudColor));
	target.draw(cloud);
}

#include "InstructionSquareCheckBorder.h"
#include "CloudRobot.h"
#include "InstructionRobot.h"




InstructionSquareCheckBorder::InstructionSquareCheckBorder(GameContext & gameContext) :
	InstructionSquareCheck(gameContext, Enums::eInstruction::CheckCloud, "Check Cloud"),
	mBorder(Enums::eDir::Right)
{
}

InstructionSquareCheckBorder::InstructionSquareCheckBorder(GameContext & gameContext, std::string & source) :
	InstructionSquareCheck(gameContext, Enums::eInstruction::CheckCloud, "Check Cloud"),
	mBorder(Enums::eDir::Right)
{
	convertFromString(source);
}

InstructionSquareCheckBorder::~InstructionSquareCheckBorder()
{
}

Enums::eDir InstructionSquareCheckBorder::getBorder()
{
	return mBorder;
}

void InstructionSquareCheckBorder::setBorder(Enums::eDir newBorder)
{
	mBorder = newBorder;
}

std::list<Enums::eInstructionModifier> InstructionSquareCheckBorder::getPossibleModifications()
{
	return { Enums::eInstructionModifier::NextDirTrue, Enums::eInstructionModifier::NextDirFalse, Enums::eInstructionModifier::CheckDir, Enums::eInstructionModifier::RobotColor, Enums::eInstructionModifier::CloudDir };
}

void InstructionSquareCheckBorder::applyModification(InstructionModificationData modificationData)
{
	switch (modificationData.modification)
	{
	case Enums::eInstructionModifier::CloudDir: setBorder(modificationData.dirData); break;
	default: InstructionSquareCheck::applyModification(modificationData); break;
	}
}

std::string InstructionSquareCheckBorder::convertToString()
{
	return Enums::getString(getType()) + Enums::getString(getNextTrueDir()) + Enums::getString(getNextFalseDir()) + Enums::getString(getCheckDir()) + Enums::getString(getRobotColor()) + Enums::getString(getBorder());
}

bool InstructionSquareCheckBorder::convertFromString(std::string & source)
{
	if (source.substr(0, 2) == Enums::getString(getType()) && source.size() >= 7)
	{
		setNextTrueDir(Enums::getDirFromString(source[2]));
		setNextFalseDir(Enums::getDirFromString(source[3]));
		setCheckDir(Enums::getDirFromString(source[4]));
		setRobotColor(Enums::getColorFromString(source[5]));
		setBorder(Enums::getDirFromString(source[6]));

		return true;
	}
	else
	{
		return false;
	}
}

bool InstructionSquareCheckBorder::performCheck(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, unsigned int toChecki, unsigned int toCheckj)
{

	return (canvas.getIsBorder(toChecki, toCheckj, mBorder));
}

void InstructionSquareCheckBorder::drawInterior(sf::RenderTarget & target)
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

	sf::ConvexShape borderUp;
	borderUp.setPointCount(6);
	borderUp.setPoint(0, sf::Vector2f(0.1f, 0.0f));
	borderUp.setPoint(1, sf::Vector2f(0.05f, 0.05f));
	borderUp.setPoint(2, sf::Vector2f(0.1f, 0.1f));
	borderUp.setPoint(3, sf::Vector2f(0.3f, 0.1f));
	borderUp.setPoint(4, sf::Vector2f(0.35f, 0.05f));
	borderUp.setPoint(5, sf::Vector2f(0.3f, 0.0f));
	borderUp.scale(mBoundingBox*3.0f / 4.0f);
	borderUp.move(sf::Vector2f(0.55f*mBoundingBox.x*3.0f / 4.0f, 0.55f*mBoundingBox.y*3.0f / 4.0f));
	borderUp.move(mTopLeftCorner + mBoundingBox / 8.0f);
	borderUp.setFillColor(mBorder==Enums::eDir::Up ? sf::Color(0, 0, 0) : sf::Color(127, 127, 127));
	target.draw(borderUp);

	sf::ConvexShape borderDown;
	borderDown.setPointCount(6);
	borderDown.setPoint(0, sf::Vector2f(0.1f, 0.4f));
	borderDown.setPoint(1, sf::Vector2f(0.05f, 0.35f));
	borderDown.setPoint(2, sf::Vector2f(0.1f, 0.3f));
	borderDown.setPoint(3, sf::Vector2f(0.3f, 0.3f));
	borderDown.setPoint(4, sf::Vector2f(0.35f, 0.35f));
	borderDown.setPoint(5, sf::Vector2f(0.3f, 0.4f));
	borderDown.scale(mBoundingBox*3.0f / 4.0f);
	borderDown.move(sf::Vector2f(0.55f*mBoundingBox.x*3.0f / 4.0f, 0.55f*mBoundingBox.y*3.0f / 4.0f));
	borderDown.move(mTopLeftCorner + mBoundingBox / 8.0f);
	borderDown.setFillColor(mBorder == Enums::eDir::Down ? sf::Color(0, 0, 0) : sf::Color(127, 127, 127));
	target.draw(borderDown);

	sf::ConvexShape borderLeft;
	borderLeft.setPointCount(6);
	borderLeft.setPoint(0, sf::Vector2f(0.0f, 0.1f));
	borderLeft.setPoint(1, sf::Vector2f(0.05f, 0.05f));
	borderLeft.setPoint(2, sf::Vector2f(0.1f, 0.1f));
	borderLeft.setPoint(3, sf::Vector2f(0.1f, 0.3f));
	borderLeft.setPoint(4, sf::Vector2f(0.05f, 0.35f));
	borderLeft.setPoint(5, sf::Vector2f(0.0f, 0.3f));
	borderLeft.scale(mBoundingBox*3.0f / 4.0f);
	borderLeft.move(sf::Vector2f(0.55f*mBoundingBox.x*3.0f / 4.0f, 0.55f*mBoundingBox.y*3.0f / 4.0f));
	borderLeft.move(mTopLeftCorner + mBoundingBox / 8.0f);
	borderLeft.setFillColor(mBorder == Enums::eDir::Left ? sf::Color(0, 0, 0) : sf::Color(127, 127, 127));
	target.draw(borderLeft);

	sf::ConvexShape borderRight;
	borderRight.setPointCount(6);
	borderRight.setPoint(0, sf::Vector2f(0.4f, 0.1f));
	borderRight.setPoint(1, sf::Vector2f(0.35f, 0.05f));
	borderRight.setPoint(2, sf::Vector2f(0.3f, 0.1f));
	borderRight.setPoint(3, sf::Vector2f(0.3f, 0.3f));
	borderRight.setPoint(4, sf::Vector2f(0.35f, 0.35f));
	borderRight.setPoint(5, sf::Vector2f(0.4f, 0.3f));
	borderRight.scale(mBoundingBox*3.0f / 4.0f);
	borderRight.move(sf::Vector2f(0.55f*mBoundingBox.x*3.0f / 4.0f, 0.55f*mBoundingBox.y*3.0f / 4.0f));
	borderRight.move(mTopLeftCorner + mBoundingBox / 8.0f);
	borderRight.setFillColor(mBorder == Enums::eDir::Right ? sf::Color(0, 0, 0) : sf::Color(127, 127, 127));
	target.draw(borderRight);
}

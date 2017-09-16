#include <iostream>
#include "InstructionSquareActMove.h"
#include "CloudRobot.h"
#include "Game.h"



InstructionSquareActMove::InstructionSquareActMove(GameContext& gameContext) :
	InstructionSquare(gameContext, Enums::eInstruction::ActMove, "Move Action"),
	mToMove(Enums::eDir::Right)
{
	std::cout << "Creating GameEntity : InstructionSquareActMove." << std::endl;
}

InstructionSquareActMove::InstructionSquareActMove(GameContext& gameContext, std::wstring & source) :
	InstructionSquare(gameContext, Enums::eInstruction::ActMove, "Move Action"),
	mToMove(Enums::eDir::Right)
{
	convertFromString(source);
}


InstructionSquareActMove::~InstructionSquareActMove()
{
}

bool InstructionSquareActMove::isValid()
{
	return InstructionSquare::isValid() && Enums::isValid(getRobotColor(), mGameContext);
}

bool InstructionSquareActMove::applyInstruction(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, float progress)
{
	switch (mToMove)
	{
	case Enums::eDir::Center: return true;
	case Enums::eDir::Left: return cloudRobot.moveLeft(progress);
	case Enums::eDir::Right: return cloudRobot.moveRight(progress);
	case Enums::eDir::Up: return cloudRobot.moveUp(progress);
	case Enums::eDir::Down: return cloudRobot.moveDown(progress);
	default: return true;
	}

	return true;
}

void InstructionSquareActMove::animateInstruction(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, float progress, float lastProgress)
{
	if (progress > 0.0f && lastProgress <= 0.0f)
	{
		mGameContext.resourceHandler.playSound(SoundHandler::eSound::SFXMove);
	}

	float rot = 45.0f * (progress < 0.2f ? (progress / 0.2f) : (progress > 0.8f ? (1.0f - progress) / 0.2f : 1.0f));

	if (mToMove == Enums::eDir::Up)
	{
		rot /= 4.0f;
	}

	switch (mToMove)
	{
	case Enums::eDir::Left: cloudRobot.animateBody(-rot, -rot, -rot, -rot, false); break;
	case Enums::eDir::Right: cloudRobot.animateBody(rot, rot, rot, rot, false); break;
	case Enums::eDir::Up: cloudRobot.animateBody(rot, -rot, rot, -rot, true); break;
	case Enums::eDir::Down: cloudRobot.animateBody(-rot, rot, -rot, rot, true); break;
	}
}

void InstructionSquareActMove::drawInterior(sf::RenderTarget & target)
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

	sf::ConvexShape direction;
	direction.setPointCount(3);
	switch (mToMove)
	{
	case Enums::eDir::Left:
		direction.setPoint(0, sf::Vector2f(0.4f, 0.0f));
		direction.setPoint(1, sf::Vector2f(0.4f, 0.4f));
		direction.setPoint(2, sf::Vector2f(0.0f, 0.2f));
		break;
	case Enums::eDir::Right:
		direction.setPoint(0, sf::Vector2f(0.0f, 0.0f));
		direction.setPoint(1, sf::Vector2f(0.0f, 0.4f));
		direction.setPoint(2, sf::Vector2f(0.4f, 0.2f));
		break;
	case Enums::eDir::Up:
		direction.setPoint(0, sf::Vector2f(0.0f, 0.4f));
		direction.setPoint(1, sf::Vector2f(0.4f, 0.4f));
		direction.setPoint(2, sf::Vector2f(0.2f, 0.0f));
		break;
	case Enums::eDir::Down:
		direction.setPoint(0, sf::Vector2f(0.0f, 0.0f));
		direction.setPoint(1, sf::Vector2f(0.4f, 0.0f));
		direction.setPoint(2, sf::Vector2f(0.2f, 0.4f));
		break;
	}
	direction.scale(mBoundingBox*3.0f / 4.0f);
	direction.move(sf::Vector2f(0.55f*mBoundingBox.x*3.0f / 4.0f, 0.3f*mBoundingBox.y*3.0f / 4.0f));
	direction.move(mTopLeftCorner + mBoundingBox / 8.0f);
	direction.setFillColor(sf::Color(127, 127, 127));
	target.draw(direction);
}

Enums::eDir InstructionSquareActMove::getToMove()
{
	return mToMove;
}

void InstructionSquareActMove::setToMove(Enums::eDir newDir)
{
	mToMove = newDir;
}

std::list<Enums::eInstructionModifier> InstructionSquareActMove::getPossibleModifications()
{
	return { Enums::eInstructionModifier::NextDir, Enums::eInstructionModifier::CloudDir, Enums::eInstructionModifier::RobotColor };
}

void InstructionSquareActMove::applyModification(InstructionModificationData modificationData)
{
	switch (modificationData.modification)
	{
	case Enums::eInstructionModifier::NextDir: setNextDir(modificationData.dirData); break;
	case Enums::eInstructionModifier::CloudDir: setToMove(modificationData.dirData); break;
	case Enums::eInstructionModifier::RobotColor: setRobotColor(modificationData.colorData); break;
	default: InstructionSquare::applyModification(modificationData); break;
	}
}

std::wstring InstructionSquareActMove::convertToString()
{
	return Enums::getString(getType()) + Enums::getString(getNextDir()) + Enums::getString(getToMove()) + Enums::getString(getRobotColor());
}

bool InstructionSquareActMove::convertFromString(std::wstring & source)
{
	if (source.substr(0, 2) == Enums::getString(getType()) && source.size() >= 5)
	{
		setNextDir(Enums::getDirFromString(source[2]));
		setToMove(Enums::getDirFromString(source[3]));
		setRobotColor(Enums::getColorFromString(source[4]));

		return true;
	}
	else
	{
		return false;
	}
}

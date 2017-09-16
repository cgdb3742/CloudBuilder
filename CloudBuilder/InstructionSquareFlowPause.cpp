#include "InstructionSquareFlowPause.h"




InstructionSquareFlowPause::InstructionSquareFlowPause(GameContext & gameContext) :
	InstructionSquare(gameContext, Enums::eInstruction::FlowPause, "Pause")
{
}

InstructionSquareFlowPause::InstructionSquareFlowPause(GameContext & gameContext, std::wstring source) :
	InstructionSquare(gameContext, Enums::eInstruction::FlowPause, "Pause")
{
	convertFromString(source);
}

InstructionSquareFlowPause::~InstructionSquareFlowPause()
{
}

bool InstructionSquareFlowPause::isValid()
{
	return InstructionSquare::isValid() && Enums::isValid(getRobotColor(), mGameContext);
}

std::list<Enums::eInstructionModifier> InstructionSquareFlowPause::getPossibleModifications()
{
	return { Enums::eInstructionModifier::NextDir, Enums::eInstructionModifier::RobotColor };
}

void InstructionSquareFlowPause::applyModification(InstructionModificationData modificationData)
{
	switch (modificationData.modification)
	{
	case Enums::eInstructionModifier::NextDir: setNextDir(modificationData.dirData); break;
	case Enums::eInstructionModifier::RobotColor: setRobotColor(modificationData.colorData); break;
	default: InstructionSquare::applyModification(modificationData); break;
	}
}

std::wstring InstructionSquareFlowPause::convertToString()
{
	return Enums::getString(getType()) + Enums::getString(getNextDir()) + Enums::getString(getRobotColor());
}

bool InstructionSquareFlowPause::convertFromString(std::wstring & source)
{
	if (source.substr(0, 2) == Enums::getString(getType()) && source.size() >= 4)
	{
		setNextDir(Enums::getDirFromString(source[2]));
		setRobotColor(Enums::getColorFromString(source[3]));

		return true;
	}
	else
	{
		return false;
	}
}

void InstructionSquareFlowPause::drawInterior(sf::RenderTarget & target)
{
	sf::RectangleShape square(mBoundingBox*3.0f / 4.0f);
	square.setPosition(mTopLeftCorner + mBoundingBox / 8.0f);
	square.setFillColor(sf::Color(0, 63, 63));
	square.setOutlineThickness(1.0f);
	square.setOutlineColor(sf::Color(0, 0, 0));
	target.draw(square);

	sf::ConvexShape iconLeft;
	iconLeft.setPointCount(4);
	iconLeft.setPoint(0, sf::Vector2f(0.2f, 0.1f));
	iconLeft.setPoint(1, sf::Vector2f(0.4f, 0.1f));
	iconLeft.setPoint(2, sf::Vector2f(0.4f, 0.9f));
	iconLeft.setPoint(3, sf::Vector2f(0.2f, 0.9f));
	iconLeft.scale(mBoundingBox*3.0f / 4.0f);
	iconLeft.move(mTopLeftCorner + mBoundingBox / 8.0f);
	iconLeft.setFillColor(Enums::getColor(mRobotColor));
	target.draw(iconLeft);

	sf::ConvexShape iconRight;
	iconRight.setPointCount(4);
	iconRight.setPoint(0, sf::Vector2f(0.6f, 0.1f));
	iconRight.setPoint(1, sf::Vector2f(0.8f, 0.1f));
	iconRight.setPoint(2, sf::Vector2f(0.8f, 0.9f));
	iconRight.setPoint(3, sf::Vector2f(0.6f, 0.9f));
	iconRight.scale(mBoundingBox*3.0f / 4.0f);
	iconRight.move(mTopLeftCorner + mBoundingBox / 8.0f);
	iconRight.setFillColor(Enums::getColor(mRobotColor));
	target.draw(iconRight);
}

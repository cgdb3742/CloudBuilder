#include "InstructionSquareFlowWait.h"





InstructionSquareFlowWait::InstructionSquareFlowWait(GameContext & gameContext) :
	InstructionSquare(gameContext, Enums::eInstruction::FlowWait, "Wait")
{
}

InstructionSquareFlowWait::InstructionSquareFlowWait(GameContext & gameContext, std::wstring source) :
	InstructionSquare(gameContext, Enums::eInstruction::FlowWait, "Wait")
{
	convertFromString(source);
}

InstructionSquareFlowWait::~InstructionSquareFlowWait()
{
}

std::list<Enums::eInstructionModifier> InstructionSquareFlowWait::getPossibleModifications()
{
	return { Enums::eInstructionModifier::NextDir };
}

void InstructionSquareFlowWait::applyModification(InstructionModificationData modificationData)
{
	switch (modificationData.modification)
	{
	case Enums::eInstructionModifier::NextDir: setNextDir(modificationData.dirData); break;
	default: InstructionSquare::applyModification(modificationData); break;
	}
}

std::wstring InstructionSquareFlowWait::convertToString()
{
	return Enums::getString(getType()) + Enums::getString(getNextDir());
}

bool InstructionSquareFlowWait::convertFromString(std::wstring & source)
{
	if (source.substr(0, 2) == Enums::getString(getType()) && source.size() >= 3)
	{
		setNextDir(Enums::getDirFromString(source[2]));

		return true;
	}
	else
	{
		return false;
	}
}

void InstructionSquareFlowWait::drawInterior(sf::RenderTarget & target)
{
	sf::RectangleShape square(mBoundingBox*3.0f / 4.0f);
	square.setPosition(mTopLeftCorner + mBoundingBox / 8.0f);
	square.setFillColor(sf::Color(0, 63, 63));
	square.setOutlineThickness(1.0f);
	square.setOutlineColor(sf::Color(0, 0, 0));
	target.draw(square);

	sf::ConvexShape iconLeft;
	iconLeft.setPointCount(3);
	iconLeft.setPoint(0, sf::Vector2f(0.1f, 0.1f));
	iconLeft.setPoint(1, sf::Vector2f(0.5f, 0.5f));
	iconLeft.setPoint(2, sf::Vector2f(0.1f, 0.9f));
	iconLeft.scale(mBoundingBox*3.0f / 4.0f);
	iconLeft.move(mTopLeftCorner + mBoundingBox / 8.0f);
	iconLeft.setFillColor(sf::Color(127, 127, 127));
	target.draw(iconLeft);

	sf::ConvexShape iconRight;
	iconRight.setPointCount(3);
	iconRight.setPoint(0, sf::Vector2f(0.5f, 0.1f));
	iconRight.setPoint(1, sf::Vector2f(0.9f, 0.5f));
	iconRight.setPoint(2, sf::Vector2f(0.5f, 0.9f));
	iconRight.scale(mBoundingBox*3.0f / 4.0f);
	iconRight.move(mTopLeftCorner + mBoundingBox / 8.0f);
	iconRight.setFillColor(sf::Color(127, 127, 127));
	target.draw(iconRight);
}

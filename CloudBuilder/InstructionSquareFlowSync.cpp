#include "InstructionSquareFlowSync.h"



InstructionSquareFlowSync::InstructionSquareFlowSync(GameContext & gameContext) :
	InstructionSquare(gameContext, Enums::eInstruction::FlowSync, "Sync")
{
}

InstructionSquareFlowSync::InstructionSquareFlowSync(GameContext & gameContext, std::string source) :
	InstructionSquare(gameContext, Enums::eInstruction::FlowSync, "Sync")
{
	convertFromString(source);
}

InstructionSquareFlowSync::~InstructionSquareFlowSync()
{
}

std::list<Enums::eInstructionModifier> InstructionSquareFlowSync::getPossibleModifications()
{
	return { Enums::eInstructionModifier::NextDir };
}

void InstructionSquareFlowSync::applyModification(InstructionModificationData modificationData)
{
	switch (modificationData.modification)
	{
	case Enums::eInstructionModifier::NextDir: setNextDir(modificationData.dirData); break;
	default: InstructionSquare::applyModification(modificationData); break;
	}
}

std::string InstructionSquareFlowSync::convertToString()
{
	return Enums::getString(getType()) + Enums::getString(getNextDir());
}

bool InstructionSquareFlowSync::convertFromString(std::string & source)
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

void InstructionSquareFlowSync::drawInterior(sf::RenderTarget & target)
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
	iconLeft.setPoint(1, sf::Vector2f(0.4f, 0.5f));
	iconLeft.setPoint(2, sf::Vector2f(0.1f, 0.9f));
	iconLeft.scale(mBoundingBox*3.0f / 4.0f);
	iconLeft.move(mTopLeftCorner + mBoundingBox / 8.0f);
	iconLeft.setFillColor(sf::Color(127, 127, 127));
	target.draw(iconLeft);

	sf::ConvexShape iconMiddle;
	iconMiddle.setPointCount(3);
	iconMiddle.setPoint(0, sf::Vector2f(0.4f, 0.1f));
	iconMiddle.setPoint(1, sf::Vector2f(0.7f, 0.5f));
	iconMiddle.setPoint(2, sf::Vector2f(0.4f, 0.9f));
	iconMiddle.scale(mBoundingBox*3.0f / 4.0f);
	iconMiddle.move(mTopLeftCorner + mBoundingBox / 8.0f);
	iconMiddle.setFillColor(sf::Color(127, 127, 127));
	target.draw(iconMiddle);

	sf::ConvexShape iconRight;
	iconRight.setPointCount(4);
	iconRight.setPoint(0, sf::Vector2f(0.7f, 0.1f));
	iconRight.setPoint(1, sf::Vector2f(0.9f, 0.1f));
	iconRight.setPoint(2, sf::Vector2f(0.9f, 0.9f));
	iconRight.setPoint(3, sf::Vector2f(0.7f, 0.9f));
	iconRight.scale(mBoundingBox*3.0f / 4.0f);
	iconRight.move(mTopLeftCorner + mBoundingBox / 8.0f);
	iconRight.setFillColor(sf::Color(127, 127, 127));
	target.draw(iconRight);
}

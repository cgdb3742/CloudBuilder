#include "InstructionSquareReject.h"
#include "InstructionRobot.h"


InstructionSquareReject::InstructionSquareReject() :
	InstructionSquare(Enums::eInstruction::SpeReject, "Reject")
{
}

InstructionSquareReject::InstructionSquareReject(std::string & source) :
	InstructionSquare(Enums::eInstruction::SpeReject, "Reject")
{
	convertFromString(source);
}


InstructionSquareReject::~InstructionSquareReject()
{
}

std::list<Enums::eInstructionModifier> InstructionSquareReject::getPossibleModifications()
{
	return {};
}

void InstructionSquareReject::applyModification(InstructionModificationData modificationData)
{
	InstructionSquare::applyModification(modificationData);
}

std::string InstructionSquareReject::convertToString()
{
	return Enums::getString(getType());
}

bool InstructionSquareReject::convertFromString(std::string & source)
{
	return (source.substr(0, 2) == Enums::getString(getType()));
}

bool InstructionSquareReject::applyInstruction(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, float progress)
{
	if (instructionRobot.getResult() == Enums::eResult::Running)
	{
		instructionRobot.setResult(Enums::eResult::Accept);
	}

	return true;
}

void InstructionSquareReject::drawInterior(sf::RenderTarget & target)
{
	sf::RectangleShape square(mBoundingBox*3.0f / 4.0f);
	square.setPosition(mTopLeftCorner + mBoundingBox / 8.0f);
	square.setFillColor(sf::Color(63, 0, 63));
	square.setOutlineThickness(1.0f);
	square.setOutlineColor(sf::Color(0, 0, 0));
	target.draw(square);

	sf::ConvexShape iconRejectBar;
	iconRejectBar.setPointCount(4);
	iconRejectBar.setPoint(0, sf::Vector2f(0.75f, 0.125f));
	iconRejectBar.setPoint(1, sf::Vector2f(0.125f, 0.75f));
	iconRejectBar.setPoint(2, sf::Vector2f(0.25f, 0.875f));
	iconRejectBar.setPoint(3, sf::Vector2f(0.875f, 0.25f));
	iconRejectBar.scale(mBoundingBox*3.0f / 4.0f);
	iconRejectBar.move(mTopLeftCorner + mBoundingBox / 8.0f);
	iconRejectBar.setFillColor(sf::Color(255, 0, 0));
	target.draw(iconRejectBar);

	sf::ConvexShape iconRejectUpLeft;
	iconRejectUpLeft.setPointCount(4);
	iconRejectUpLeft.setPoint(0, sf::Vector2f(0.125f, 0.25f));
	iconRejectUpLeft.setPoint(1, sf::Vector2f(0.375f, 0.5f));
	iconRejectUpLeft.setPoint(2, sf::Vector2f(0.5f, 0.375f));
	iconRejectUpLeft.setPoint(3, sf::Vector2f(0.25f, 0.125f));
	iconRejectUpLeft.scale(mBoundingBox*3.0f / 4.0f);
	iconRejectUpLeft.move(mTopLeftCorner + mBoundingBox / 8.0f);
	iconRejectUpLeft.setFillColor(sf::Color(255, 0, 0));
	target.draw(iconRejectUpLeft);

	sf::ConvexShape iconRejectDownRight;
	iconRejectDownRight.setPointCount(4);
	iconRejectDownRight.setPoint(0, sf::Vector2f(0.875f, 0.75f));
	iconRejectDownRight.setPoint(1, sf::Vector2f(0.625f, 0.5f));
	iconRejectDownRight.setPoint(2, sf::Vector2f(0.5f, 0.625f));
	iconRejectDownRight.setPoint(3, sf::Vector2f(0.75f, 0.875f));
	iconRejectDownRight.scale(mBoundingBox*3.0f / 4.0f);
	iconRejectDownRight.move(mTopLeftCorner + mBoundingBox / 8.0f);
	iconRejectDownRight.setFillColor(sf::Color(255, 0, 0));
	target.draw(iconRejectDownRight);
}

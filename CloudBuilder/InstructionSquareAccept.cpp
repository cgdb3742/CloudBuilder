#include "InstructionSquareAccept.h"
#include "InstructionRobot.h"
#include "Game.h"


InstructionSquareAccept::InstructionSquareAccept(GameContext& gameContext) :
	InstructionSquare(gameContext, Enums::eInstruction::SpeAccept, "Accept")
{
}

InstructionSquareAccept::InstructionSquareAccept(GameContext& gameContext, std::string & source) :
	InstructionSquare(gameContext, Enums::eInstruction::SpeAccept, "Accept")
{
	convertFromString(source);
}


InstructionSquareAccept::~InstructionSquareAccept()
{
}

std::list<Enums::eInstructionModifier> InstructionSquareAccept::getPossibleModifications()
{
	return {};
}

void InstructionSquareAccept::applyModification(InstructionModificationData modificationData)
{
	InstructionSquare::applyModification(modificationData);
}

std::string InstructionSquareAccept::convertToString()
{
	return Enums::getString(getType());
}

bool InstructionSquareAccept::convertFromString(std::string & source)
{
	return (source.substr(0, 2) == Enums::getString(getType()));
}

//TODO Check if validation or modification to set the result to either accept or submit
bool InstructionSquareAccept::applyInstruction(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, float progress)
{
	if (instructionRobot.getResult() == Enums::eResult::Running)
	{
		if (mGameContext.levelData.isValidation)
		{
			instructionRobot.setResult(Enums::eResult::Accept);
		}
		else
		{
			instructionRobot.setResult(Enums::eResult::Submit);
		}
	}

	return true;
}

void InstructionSquareAccept::drawInterior(sf::RenderTarget & target)
{
	sf::RectangleShape square(mBoundingBox*3.0f / 4.0f);
	square.setPosition(mTopLeftCorner + mBoundingBox / 8.0f);
	square.setFillColor(sf::Color(63, 0, 63));
	square.setOutlineThickness(1.0f);
	square.setOutlineColor(sf::Color(0, 0, 0));
	target.draw(square);

	sf::ConvexShape acceptLeft;
	acceptLeft.setPointCount(4);
	acceptLeft.setPoint(0, sf::Vector2f(0.125f, 0.625f));
	acceptLeft.setPoint(1, sf::Vector2f(0.375f, 0.875f));
	acceptLeft.setPoint(2, sf::Vector2f(0.375f, 0.625f));
	acceptLeft.setPoint(3, sf::Vector2f(0.25f, 0.5f));
	acceptLeft.scale(mBoundingBox*3.0f / 4.0f);
	acceptLeft.move(mTopLeftCorner + mBoundingBox / 8.0f);
	acceptLeft.setFillColor(sf::Color(0, 255, 0));
	target.draw(acceptLeft);

	sf::ConvexShape acceptRight;
	acceptRight.setPointCount(4);
	acceptRight.setPoint(0, sf::Vector2f(0.875f, 0.375f));
	acceptRight.setPoint(1, sf::Vector2f(0.375f, 0.875f));
	acceptRight.setPoint(2, sf::Vector2f(0.375f, 0.625f));
	acceptRight.setPoint(3, sf::Vector2f(0.75f, 0.25f));
	acceptRight.scale(mBoundingBox*3.0f / 4.0f);
	acceptRight.move(mTopLeftCorner + mBoundingBox / 8.0f);
	acceptRight.setFillColor(sf::Color(0, 255, 0));
	target.draw(acceptRight);
}

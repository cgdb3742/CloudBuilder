#include "InstructionSquareStart.h"



InstructionSquareStart::InstructionSquareStart(GameContext& gameContext) :
	InstructionSquare(gameContext, Enums::eInstruction::SpeStart, "Robot Start"),
	mColor(Enums::eColor::NoColor)
{
}

InstructionSquareStart::InstructionSquareStart(GameContext& gameContext, std::wstring & source) :
	InstructionSquare(gameContext, Enums::eInstruction::SpeStart, "Robot Start"),
	mColor(Enums::eColor::NoColor)
{
	convertFromString(source);
}

InstructionSquareStart::InstructionSquareStart(GameContext& gameContext, Enums::eColor color) :
	InstructionSquare(gameContext, Enums::eInstruction::SpeStart, "Robot Start"),
	mColor(color)
{
}


InstructionSquareStart::~InstructionSquareStart()
{
}

bool InstructionSquareStart::isValid()
{
	return InstructionSquare::isValid() && (getStartColor()!=Enums::eColor::NoColor) && Enums::isValid(getStartColor(), mGameContext);
}

std::list<Enums::eInstructionModifier> InstructionSquareStart::getPossibleModifications()
{
	return { Enums::eInstructionModifier::NextDir };
}

void InstructionSquareStart::applyModification(InstructionModificationData modificationData)
{
	switch (modificationData.modification)
	{
	case Enums::eInstructionModifier::NextDir: setNextDir(modificationData.dirData); break;
	//case Enums::eInstructionModifier::RobotColor: setStartColor(modificationData.colorData); break; //Should be unhautorized to a Start of each, or maybe swap Starts ?
	default: InstructionSquare::applyModification(modificationData); break;
	}
}

std::wstring InstructionSquareStart::convertToString()
{
	return Enums::getString(getType()) + Enums::getString(getNextDir()) + Enums::getString(getStartColor());
}

bool InstructionSquareStart::convertFromString(std::wstring & source)
{
	if (source.substr(0, 2) == Enums::getString(getType()) && source.size() >= 4)
	{
		setNextDir(Enums::getDirFromString(source[2]));
		setStartColor(Enums::getColorFromString(source[3]));

		return true;
	}
	else
	{
		return false;
	}
}

Enums::eColor InstructionSquareStart::getStartColor()
{
	return mColor;
}

void InstructionSquareStart::setStartColor(Enums::eColor newColor)
{
	mColor = newColor;
}

void InstructionSquareStart::drawInterior(sf::RenderTarget & target)
{
	sf::RectangleShape square(mBoundingBox*3.0f / 4.0f);
	square.setPosition(mTopLeftCorner + mBoundingBox / 8.0f);
	square.setFillColor(sf::Color(63, 0, 63));
	square.setOutlineThickness(1.0f);
	square.setOutlineColor(sf::Color(0, 0, 0));
	target.draw(square);

	sf::ConvexShape iconStart;
	iconStart.setPointCount(4);
	iconStart.setPoint(0, sf::Vector2f(0.1f, 0.1f));
	iconStart.setPoint(1, sf::Vector2f(0.3f, 0.1f));
	iconStart.setPoint(2, sf::Vector2f(0.3f, 0.9f));
	iconStart.setPoint(3, sf::Vector2f(0.1f, 0.9f));
	iconStart.scale(mBoundingBox*3.0f / 4.0f);
	iconStart.move(mTopLeftCorner + mBoundingBox / 8.0f);
	iconStart.setFillColor(Enums::getColor(mColor));
	target.draw(iconStart);

	sf::ConvexShape iconPlay;
	iconPlay.setPointCount(3);
	iconPlay.setPoint(0, sf::Vector2f(0.5f, 0.1f));
	iconPlay.setPoint(1, sf::Vector2f(0.9f, 0.5f));
	iconPlay.setPoint(2, sf::Vector2f(0.5f, 0.9f));
	iconPlay.scale(mBoundingBox*3.0f / 4.0f);
	iconPlay.move(mTopLeftCorner + mBoundingBox / 8.0f);
	iconPlay.setFillColor(Enums::getColor(mColor));
	target.draw(iconPlay);
}

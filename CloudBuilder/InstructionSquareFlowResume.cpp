#include "InstructionSquareFlowResume.h"




InstructionSquareFlowResume::InstructionSquareFlowResume(GameContext & gameContext) :
	InstructionSquare(gameContext, Enums::eInstruction::FlowResume, "Resume")
{
}

InstructionSquareFlowResume::InstructionSquareFlowResume(GameContext & gameContext, std::wstring source) :
	InstructionSquare(gameContext, Enums::eInstruction::FlowResume, "Resume")
{
	convertFromString(source);
}

InstructionSquareFlowResume::~InstructionSquareFlowResume()
{
}

bool InstructionSquareFlowResume::isValid()
{
	return InstructionSquare::isValid() && Enums::isValid(getRobotColor(), mGameContext);
}

std::list<Enums::eInstructionModifier> InstructionSquareFlowResume::getPossibleModifications()
{
	return { Enums::eInstructionModifier::NextDir, Enums::eInstructionModifier::RobotColor };
}

void InstructionSquareFlowResume::applyModification(InstructionModificationData modificationData)
{
	switch (modificationData.modification)
	{
	case Enums::eInstructionModifier::NextDir: setNextDir(modificationData.dirData); break;
	case Enums::eInstructionModifier::RobotColor: setRobotColor(modificationData.colorData); break;
	default: InstructionSquare::applyModification(modificationData); break;
	}
}

std::wstring InstructionSquareFlowResume::convertToString()
{
	return Enums::getString(getType()) + Enums::getString(getNextDir()) + Enums::getString(getRobotColor());
}

bool InstructionSquareFlowResume::convertFromString(std::wstring & source)
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

void InstructionSquareFlowResume::drawInterior(sf::RenderTarget & target)
{
	sf::RectangleShape square(mBoundingBox*3.0f / 4.0f);
	square.setPosition(mTopLeftCorner + mBoundingBox / 8.0f);
	square.setFillColor(sf::Color(0, 63, 63));
	square.setOutlineThickness(1.0f);
	square.setOutlineColor(sf::Color(0, 0, 0));
	target.draw(square);

	sf::ConvexShape icon;
	icon.setPointCount(3);
	icon.setPoint(0, sf::Vector2f(0.2f, 0.1f));
	icon.setPoint(1, sf::Vector2f(0.8f, 0.5f));
	icon.setPoint(2, sf::Vector2f(0.2f, 0.9f));
	icon.scale(mBoundingBox*3.0f / 4.0f);
	icon.move(mTopLeftCorner + mBoundingBox / 8.0f);
	icon.setFillColor(Enums::getColor(mRobotColor));
	target.draw(icon);
}

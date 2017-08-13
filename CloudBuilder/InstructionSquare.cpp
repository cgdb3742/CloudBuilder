#include <iostream>
#include "InstructionSquare.h"
#include "CloudCanvas.h"
#include "InstructionRobot.h"

#include "InstructionSquareStart.h"
#include "InstructionSquareAccept.h"
#include "InstructionSquareReject.h"
#include "InstructionSquareActMove.h"
#include "InstructionSquareCheckCloud.h"



std::unique_ptr<InstructionSquare> InstructionSquare::createNewInstructionSquare(Enums::eInstruction type)
{
	return createNewInstructionSquare(type, Enums::eColor::NoColor);
}

std::unique_ptr<InstructionSquare> InstructionSquare::createNewInstructionSquare(Enums::eInstruction type, Enums::eColor color)
{
	switch (type)
	{
	case Enums::eInstruction::Unassigned: return std::make_unique<InstructionSquare>(InstructionSquare());
	case Enums::eInstruction::SpeStart: return std::make_unique<InstructionSquareStart>(InstructionSquareStart(color));
	case Enums::eInstruction::SpeAccept: return std::make_unique<InstructionSquareAccept>(InstructionSquareAccept());
	case Enums::eInstruction::SpeReject: return std::make_unique<InstructionSquareReject>(InstructionSquareReject());
	case Enums::eInstruction::ActMove: return std::make_unique<InstructionSquareActMove>(InstructionSquareActMove());
	case Enums::eInstruction::CheckCloud: return std::make_unique<InstructionSquareCheckCloud>(InstructionSquareCheckCloud());
	default: return std::make_unique<InstructionSquare>(InstructionSquare());
	}
}

std::unique_ptr<InstructionSquare> InstructionSquare::createNewInstructionSquare(std::string source)
{
	switch (Enums::getInstructionFromString(source.substr(0, 2)))
	{
	case Enums::eInstruction::Unassigned: return std::make_unique<InstructionSquare>(InstructionSquare(source));
	case Enums::eInstruction::SpeStart: return std::make_unique<InstructionSquareStart>(InstructionSquareStart(source));
	case Enums::eInstruction::SpeAccept: return std::make_unique<InstructionSquareAccept>(InstructionSquareAccept(source));
	case Enums::eInstruction::SpeReject: return std::make_unique<InstructionSquareReject>(InstructionSquareReject(source));
	case Enums::eInstruction::ActMove: return std::make_unique<InstructionSquareActMove>(InstructionSquareActMove(source));
	case Enums::eInstruction::CheckCloud: return std::make_unique<InstructionSquareCheckCloud>(InstructionSquareCheckCloud(source));
	default: return nullptr;
	}

	return nullptr;
}

//InstructionSquare InstructionSquare::createNewInstructionSquareRaw(Enums::eInstruction type)
//{
//	return createNewInstructionSquareRaw(type, Enums::eColor::NoColor);
//}
//
//InstructionSquare InstructionSquare::createNewInstructionSquareRaw(Enums::eInstruction type, Enums::eColor color)
//{
//	switch (type)
//	{
//	case Enums::eInstruction::Unassigned: return InstructionSquare();
//	case Enums::eInstruction::SpeStart: return InstructionSquareStart(color);
//	case Enums::eInstruction::ActMove: return InstructionSquareActMove();
//	case Enums::eInstruction::CheckCloud: return InstructionSquareCheckCloud();
//	default: return InstructionSquare();
//	}
//}

InstructionSquare::InstructionSquare() :
	mType(Enums::eInstruction::Unassigned),
	mName("Unassigned"),
	mNext(Enums::eDir::Center)
{
	//std::cout << "Creating GameEntity : InstructionSquare." << std::endl;
}

InstructionSquare::InstructionSquare(std::string & source) :
	mType(Enums::eInstruction::Unassigned),
	mName("Unassigned"),
	mNext(Enums::eDir::Center)
{
	convertFromString(source);
}

InstructionSquare::InstructionSquare(Enums::eInstruction type, std::string name):
	mType(type),
	mName(name),
	mNext(Enums::eDir::Center)
{
	//std::cout << "Creating GameEntity : InstructionSquare." << std::endl;
}

void InstructionSquare::drawNextDir(sf::RenderTarget & target)
{
	if (mNext != Enums::eDir::Center)
	{
		sf::ConvexShape arrow;
		arrow.setPointCount(4);
		
		switch (mNext)
		{
		case Enums::eDir::Left:
			arrow.setPoint(0, sf::Vector2f(0.125f, 0.125f));
			arrow.setPoint(1, sf::Vector2f(0.0f, 0.5f));
			arrow.setPoint(2, sf::Vector2f(0.125f, 0.875f));
			arrow.setPoint(3, sf::Vector2f(0.0625f, 0.5f));
			break;
		case Enums::eDir::Right:
			arrow.setPoint(0, sf::Vector2f(0.875f, 0.125f));
			arrow.setPoint(1, sf::Vector2f(1.0f, 0.5f));
			arrow.setPoint(2, sf::Vector2f(0.875f, 0.875f));
			arrow.setPoint(3, sf::Vector2f(0.9375f, 0.5f));
			break;
		case Enums::eDir::Up:
			arrow.setPoint(0, sf::Vector2f(0.125f, 0.125f));
			arrow.setPoint(1, sf::Vector2f(0.5f, 0.0f));
			arrow.setPoint(2, sf::Vector2f(0.875f, 0.125f));
			arrow.setPoint(3, sf::Vector2f(0.5f, 0.0625f));
			break;
		case Enums::eDir::Down:
			arrow.setPoint(0, sf::Vector2f(0.125f, 0.875f));
			arrow.setPoint(1, sf::Vector2f(0.5f, 1.0f));
			arrow.setPoint(2, sf::Vector2f(0.875f, 0.875f));
			arrow.setPoint(3, sf::Vector2f(0.5f, 0.9375f));
			break;
		}
		arrow.setFillColor(sf::Color(0, 0, 255));
		arrow.setScale(mBoundingBox);
		arrow.setPosition(mTopLeftCorner);
		target.draw(arrow);
	}
}

void InstructionSquare::drawInterior(sf::RenderTarget & target)
{
	sf::RectangleShape square(mBoundingBox*3.0f / 4.0f);
	square.setPosition(mTopLeftCorner + mBoundingBox / 8.0f);
	square.setFillColor(sf::Color(63, 0, 0));
	square.setOutlineThickness(1.0f);
	square.setOutlineColor(sf::Color(0, 0, 0));
	target.draw(square);
}


InstructionSquare::~InstructionSquare()
{
}

bool InstructionSquare::IsAssigned()
{
	return (mType != Enums::eInstruction::Unassigned);
}

bool InstructionSquare::IsSpecial()
{
	return (mType == Enums::eInstruction::SpeStart || mType == Enums::eInstruction::SpeAccept || mType == Enums::eInstruction::SpeReject);
}

bool InstructionSquare::IsAction()
{
	return (mType == Enums::eInstruction::ActMove || mType == Enums::eInstruction::ActSetCloud || mType == Enums::eInstruction::ActSetColor);
}

bool InstructionSquare::IsCheck()
{
	return (mType == Enums::eInstruction::CheckCloud || mType == Enums::eInstruction::CheckColor || mType == Enums::eInstruction::CheckBorder);
}

bool InstructionSquare::IsFlow()
{
	return (mType == Enums::eInstruction::FlowWait || mType == Enums::eInstruction::FlowPause || mType == Enums::eInstruction::FlowResume || mType == Enums::eInstruction::FlowSync);;
}

bool InstructionSquare::IsWriteOnly()
{
	return (mType == Enums::eInstruction::ActSetCloud || mType == Enums::eInstruction::ActSetColor);
}

bool InstructionSquare::IsDraggable()
{
	return mType != Enums::eInstruction::Unassigned;
}

bool InstructionSquare::IsErasable()
{
	return mType != Enums::eInstruction::SpeStart;
}

Enums::eInstruction InstructionSquare::getType()
{
	return mType;
}

Enums::eDir InstructionSquare::getNextDir()
{
	return mNext;
}

Enums::eDir InstructionSquare::getNextDir(InstructionRobot& robot)
{
	return mNext;
}

void InstructionSquare::setNextDir(Enums::eDir newDir)
{
	mNext = newDir;
}

std::list<Enums::eInstructionModifier> InstructionSquare::getPossibleModifications()
{
	return {};
}

void InstructionSquare::applyModification(InstructionModificationData modificationData)
{
}

std::string InstructionSquare::convertToString()
{
	return Enums::getString(getType());
}

bool InstructionSquare::convertFromString(std::string & source)
{
	//if (source == Enums::getString(Enums::eInstruction::Unassigned))
	if (source.substr(0, 2) == Enums::getString(getType()))
	{
		mNext = Enums::eDir::Center;
		return true;
	}
	else
	{
		return false;
	}
}

bool InstructionSquare::applyInstruction(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, float progress)
{
	return true;
}

Enums::eColor InstructionSquare::getStartColor()
{
	return Enums::eColor::NoColor;
}

void InstructionSquare::setStartColor(Enums::eColor newColor)
{
}

void InstructionSquare::setUpNextDir(bool isLeftBorder, bool isRightBorder, bool isUpBorder, bool isDownBorder)
{
	if (mType == Enums::eInstruction::Unassigned || mType == Enums::eInstruction::SpeAccept || mType == Enums::eInstruction::SpeReject)
	{
		mNext = Enums::eDir::Center;
	}
	else
	{
		switch (mNext)
		{
		case Enums::eDir::Center: mNext = isRightBorder ? Enums::eDir::Left : Enums::eDir::Right; break;
		case Enums::eDir::Left: mNext = isLeftBorder ? Enums::eDir::Right : Enums::eDir::Left; break;
		case Enums::eDir::Right: mNext = isRightBorder ? Enums::eDir::Left : Enums::eDir::Right; break;
		case Enums::eDir::Up: mNext = isUpBorder ? Enums::eDir::Down : Enums::eDir::Up; break;
		case Enums::eDir::Down: mNext = isDownBorder ? Enums::eDir::Up : Enums::eDir::Down; break;
		}
	}
}

void InstructionSquare::drawCurrent(sf::RenderTarget & target)
{
	drawNextDir(target);
	drawInterior(target);

	//if (mNext != Enums::eDir::Center)
	//{
	//	sf::RectangleShape cloud(mBoundingBox);
	//	cloud.setPosition(mTopLeftCorner);
	//	cloud.setFillColor(sf::Color(191, 191, 191));
	//	target.draw(cloud);
	//}
}

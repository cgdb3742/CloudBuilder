#include <iostream>
#include "InstructionSquare.h"
#include "CloudCanvas.h"
#include "InstructionRobot.h"
#include "Game.h"

#include "InstructionSquareStart.h"
#include "InstructionSquareAccept.h"
#include "InstructionSquareReject.h"
#include "InstructionSquareActMove.h"
#include "InstructionSquareActCloud.h"
#include "InstructionSquareActColor.h"
#include "InstructionSquareCheckCloud.h"
#include "InstructionSquareCheckColor.h"
#include "InstructionSquareCheckBorder.h"
#include "InstructionSquareFlowWait.h"
#include "InstructionSquareFlowPause.h"
#include "InstructionSquareFlowResume.h"
#include "InstructionSquareFlowSync.h"



std::unique_ptr<InstructionSquare> InstructionSquare::createNewInstructionSquare(GameContext& gameContext, Enums::eInstruction type)
{
	return createNewInstructionSquare(gameContext, type, Enums::eColor::NoColor);
}

std::unique_ptr<InstructionSquare> InstructionSquare::createNewInstructionSquare(GameContext& gameContext, Enums::eInstruction type, Enums::eColor color)
{
	switch (type)
	{
	case Enums::eInstruction::Unassigned: return std::make_unique<InstructionSquare>(InstructionSquare(gameContext));
	case Enums::eInstruction::SpeStart: return std::make_unique<InstructionSquareStart>(InstructionSquareStart(gameContext, color));
	case Enums::eInstruction::SpeAccept: return std::make_unique<InstructionSquareAccept>(InstructionSquareAccept(gameContext));
	case Enums::eInstruction::SpeReject: return std::make_unique<InstructionSquareReject>(InstructionSquareReject(gameContext));
	case Enums::eInstruction::ActMove: return std::make_unique<InstructionSquareActMove>(InstructionSquareActMove(gameContext));
	case Enums::eInstruction::ActSetCloud: return std::make_unique<InstructionSquareActCloud>(InstructionSquareActCloud(gameContext));
	case Enums::eInstruction::ActSetColor: return std::make_unique<InstructionSquareActColor>(InstructionSquareActColor(gameContext));
	case Enums::eInstruction::CheckCloud: return std::make_unique<InstructionSquareCheckCloud>(InstructionSquareCheckCloud(gameContext));
	case Enums::eInstruction::CheckColor: return std::make_unique<InstructionSquareCheckColor>(InstructionSquareCheckColor(gameContext));
	case Enums::eInstruction::CheckBorder: return std::make_unique<InstructionSquareCheckBorder>(InstructionSquareCheckBorder(gameContext));
	case Enums::eInstruction::FlowWait: return std::make_unique<InstructionSquareFlowWait>(InstructionSquareFlowWait(gameContext));
	case Enums::eInstruction::FlowPause: return std::make_unique<InstructionSquareFlowPause>(InstructionSquareFlowPause(gameContext));
	case Enums::eInstruction::FlowResume: return std::make_unique<InstructionSquareFlowResume>(InstructionSquareFlowResume(gameContext));
	case Enums::eInstruction::FlowSync: return std::make_unique<InstructionSquareFlowSync>(InstructionSquareFlowSync(gameContext));
	default: return std::make_unique<InstructionSquare>(InstructionSquare(gameContext));
	}
}

std::unique_ptr<InstructionSquare> InstructionSquare::createNewInstructionSquare(GameContext& gameContext, std::wstring source)
{
	switch (Enums::getInstructionFromString(source.substr(0, 2)))
	{
	case Enums::eInstruction::Unassigned: return std::make_unique<InstructionSquare>(InstructionSquare(gameContext, source));
	case Enums::eInstruction::SpeStart: return std::make_unique<InstructionSquareStart>(InstructionSquareStart(gameContext, source));
	case Enums::eInstruction::SpeAccept: return std::make_unique<InstructionSquareAccept>(InstructionSquareAccept(gameContext, source));
	case Enums::eInstruction::SpeReject: return std::make_unique<InstructionSquareReject>(InstructionSquareReject(gameContext, source));
	case Enums::eInstruction::ActMove: return std::make_unique<InstructionSquareActMove>(InstructionSquareActMove(gameContext, source));
	case Enums::eInstruction::ActSetCloud: return std::make_unique<InstructionSquareActCloud>(InstructionSquareActCloud(gameContext, source));
	case Enums::eInstruction::ActSetColor: return std::make_unique<InstructionSquareActColor>(InstructionSquareActColor(gameContext, source));
	case Enums::eInstruction::CheckCloud: return std::make_unique<InstructionSquareCheckCloud>(InstructionSquareCheckCloud(gameContext, source));
	case Enums::eInstruction::CheckColor: return std::make_unique<InstructionSquareCheckColor>(InstructionSquareCheckColor(gameContext, source));
	case Enums::eInstruction::CheckBorder: return std::make_unique<InstructionSquareCheckBorder>(InstructionSquareCheckBorder(gameContext, source));
	case Enums::eInstruction::FlowWait: return std::make_unique<InstructionSquareFlowWait>(InstructionSquareFlowWait(gameContext, source));
	case Enums::eInstruction::FlowPause: return std::make_unique<InstructionSquareFlowPause>(InstructionSquareFlowPause(gameContext, source));
	case Enums::eInstruction::FlowResume: return std::make_unique<InstructionSquareFlowResume>(InstructionSquareFlowResume(gameContext, source));
	case Enums::eInstruction::FlowSync: return std::make_unique<InstructionSquareFlowSync>(InstructionSquareFlowSync(gameContext, source));
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

InstructionSquare::InstructionSquare(GameContext& gameContext) :
	GameEntity(gameContext),
	mType(Enums::eInstruction::Unassigned),
	mName("Unassigned"),
	mNext(Enums::eDir::Center),
	mRobotColor(Enums::eColor::NoColor)
{
	//std::cout << "Creating GameEntity : InstructionSquare." << std::endl;
}

InstructionSquare::InstructionSquare(GameContext& gameContext, std::wstring & source) :
	GameEntity(gameContext),
	mType(Enums::eInstruction::Unassigned),
	mName("Unassigned"),
	mNext(Enums::eDir::Center),
	mRobotColor(Enums::eColor::NoColor)
{
	convertFromString(source);
}

InstructionSquare::InstructionSquare(GameContext& gameContext, Enums::eInstruction type, std::string name):
	GameEntity(gameContext),
	mType(type),
	mName(name),
	mNext(Enums::eDir::Center),
	mRobotColor(Enums::eColor::NoColor)
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

bool InstructionSquare::isValid()
{
	//Find if type is allowed
	for (Enums::eInstruction inst : mGameContext.levelData.availableInstructions)
	{
		if (inst == getType())
		{
			return true;
		}
	}

	return false;
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

bool InstructionSquare::isPossibleNextDir(Enums::eDir dir)
{
	return (mNext == dir);
}

std::list<Enums::eInstructionModifier> InstructionSquare::getPossibleModifications()
{
	return {};
}

void InstructionSquare::applyModification(InstructionModificationData modificationData)
{
}

std::wstring InstructionSquare::convertToString()
{
	return Enums::getString(getType());
}

bool InstructionSquare::convertFromString(std::wstring & source)
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

void InstructionSquare::animateInstruction(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, float progress, float lastProgress)
{
}

Enums::eColor InstructionSquare::getRobotColor()
{
	return mRobotColor;
}

void InstructionSquare::setRobotColor(Enums::eColor newColor)
{
	mRobotColor = newColor;
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

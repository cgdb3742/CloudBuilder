#include "InstructionSquareCheck.h"
#include "CloudRobot.h"
#include "InstructionRobot.h"
#include "Game.h"




InstructionSquareCheck::InstructionSquareCheck(GameContext & gameContext):
	InstructionSquare(gameContext),
	mNextTrue(Enums::eDir::Center),
	mNextFalse(Enums::eDir::Center),
	mCheckDir(Enums::eDir::Center)
{
}

InstructionSquareCheck::InstructionSquareCheck(GameContext & gameContext, std::wstring & source):
	InstructionSquare(gameContext, source),
	mNextTrue(Enums::eDir::Center),
	mNextFalse(Enums::eDir::Center),
	mCheckDir(Enums::eDir::Center)
{
}

InstructionSquareCheck::~InstructionSquareCheck()
{
}

bool InstructionSquareCheck::isValid()
{
	return InstructionSquare::isValid() && Enums::isValid(getRobotColor(), mGameContext);
}

Enums::eDir InstructionSquareCheck::getNextDir(InstructionRobot & robot)
{
	if (robot.getLastCheck())
	{
		return mNextTrue;
	}
	else
	{
		return mNextFalse;
	}
}

Enums::eDir InstructionSquareCheck::getNextTrueDir()
{
	return mNextTrue;
}

void InstructionSquareCheck::setNextTrueDir(Enums::eDir newDir)
{
	if (newDir == mNextFalse)
	{
		mNextFalse = mNextTrue;
	}

	mNextTrue = newDir;
}

Enums::eDir InstructionSquareCheck::getNextFalseDir()
{
	return mNextFalse;
}

void InstructionSquareCheck::setNextFalseDir(Enums::eDir newDir)
{
	if (newDir == mNextTrue)
	{
		mNextTrue = mNextFalse;
	}

	mNextFalse = newDir;
}

bool InstructionSquareCheck::isPossibleNextDir(Enums::eDir dir)
{
	return (mNextTrue == dir || mNextFalse == dir);
}

Enums::eDir InstructionSquareCheck::getCheckDir()
{
	return mCheckDir;
}

void InstructionSquareCheck::setCheckDir(Enums::eDir newDir)
{
	mCheckDir = newDir;
}

std::list<Enums::eInstructionModifier> InstructionSquareCheck::getPossibleModifications()
{
	return { Enums::eInstructionModifier::NextDirTrue, Enums::eInstructionModifier::NextDirFalse, Enums::eInstructionModifier::CheckDir, Enums::eInstructionModifier::RobotColor};
}

void InstructionSquareCheck::applyModification(InstructionModificationData modificationData)
{
	switch (modificationData.modification)
	{
	case Enums::eInstructionModifier::NextDirTrue: setNextTrueDir(modificationData.dirData); break;
	case Enums::eInstructionModifier::NextDirFalse: setNextFalseDir(modificationData.dirData); break;
	case Enums::eInstructionModifier::CheckDir: setCheckDir(modificationData.dirData); break;
	case Enums::eInstructionModifier::RobotColor: setRobotColor(modificationData.colorData); break;
	default: InstructionSquare::applyModification(modificationData); break;
	}
}

bool InstructionSquareCheck::applyInstruction(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, float progress)
{
	//TODO Possibility to check an other robot ?
	unsigned int toChecki = cloudRobot.getPosi();
	unsigned int toCheckj = cloudRobot.getPosj();

	switch (mCheckDir)
	{
	case Enums::eDir::Left: toChecki--; break;
	case Enums::eDir::Right: toChecki++; break;
	case Enums::eDir::Up: toCheckj--; break;
	case Enums::eDir::Down: toCheckj++; break;
	default: break;
	}

	instructionRobot.setLastCheck(performCheck(cloudRobot, canvas, instructionRobot, toChecki, toCheckj));

	return true;
}

bool InstructionSquareCheck::performCheck(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, unsigned int toChecki, unsigned int toCheckj)
{
	return false;
}

void InstructionSquareCheck::animateInstruction(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, float progress, float lastProgress)
{
	if (progress >= 0.25f && lastProgress < 0.25f)
	{
		if (instructionRobot.getLastCheck())
		{
			mGameContext.particleHandler.createParticle(ParticleHandler::eParticle::ParticleYes, 0.5f, instructionRobot.getTopLeftCorner().x, instructionRobot.getTopLeftCorner().y - instructionRobot.getBoundingBox().y / 4.0f, instructionRobot.getBoundingBox().x / 2.0f, instructionRobot.getBoundingBox().y / 32.0f);
			mGameContext.resourceHandler.playSound(SoundHandler::eSound::SFXYes);
		}
		else
		{
			mGameContext.particleHandler.createParticle(ParticleHandler::eParticle::ParticleNo, 0.5f, instructionRobot.getTopLeftCorner().x, instructionRobot.getTopLeftCorner().y - instructionRobot.getBoundingBox().y / 4.0f, instructionRobot.getBoundingBox().x / 2.0f, instructionRobot.getBoundingBox().y / 32.0f);
			mGameContext.resourceHandler.playSound(SoundHandler::eSound::SFXNo);
		}
	}
}

void InstructionSquareCheck::setUpNextDir(bool isLeftBorder, bool isRightBorder, bool isUpBorder, bool isDownBorder)
{
	switch (mNextTrue)
	{
	case Enums::eDir::Center: mNextTrue = isRightBorder ? Enums::eDir::Left : Enums::eDir::Right; break;
	case Enums::eDir::Left: mNextTrue = isLeftBorder ? Enums::eDir::Right : Enums::eDir::Left; break;
	case Enums::eDir::Right: mNextTrue = isRightBorder ? Enums::eDir::Left : Enums::eDir::Right; break;
	case Enums::eDir::Up: mNextTrue = isUpBorder ? Enums::eDir::Down : Enums::eDir::Up; break;
	case Enums::eDir::Down: mNextTrue = isDownBorder ? Enums::eDir::Up : Enums::eDir::Down; break;
	}

	switch (mNextFalse)
	{
	case Enums::eDir::Center: mNextFalse = isRightBorder ? Enums::eDir::Left : Enums::eDir::Right; break;
	case Enums::eDir::Left: mNextFalse = isLeftBorder ? Enums::eDir::Right : Enums::eDir::Left; break;
	case Enums::eDir::Right: mNextFalse = isRightBorder ? Enums::eDir::Left : Enums::eDir::Right; break;
	case Enums::eDir::Up: mNextFalse = isUpBorder ? Enums::eDir::Down : Enums::eDir::Up; break;
	case Enums::eDir::Down: mNextFalse = isDownBorder ? Enums::eDir::Up : Enums::eDir::Down; break;
	}

	if (mNextTrue == mNextFalse) //TODO sub-optimal if mNextFalse correct and mNextTrue opposite and incorrect before placement ?
	{
		if (mNextTrue == Enums::eDir::Left || mNextTrue == Enums::eDir::Right)
		{
			mNextFalse = isDownBorder ? Enums::eDir::Up : Enums::eDir::Down;
		}
		else
		{
			mNextFalse = isRightBorder ? Enums::eDir::Left : Enums::eDir::Right;
		}
	}
}

InstructionSquareCheck::InstructionSquareCheck(GameContext & gameContext, Enums::eInstruction type, std::string name):
	InstructionSquare(gameContext, type, name),
	mNextTrue(Enums::eDir::Center),
	mNextFalse(Enums::eDir::Center),
	mCheckDir(Enums::eDir::Center)
{
}

void InstructionSquareCheck::drawNextDir(sf::RenderTarget & target)
{
	if (mNextTrue != Enums::eDir::Center)
	{
		sf::ConvexShape arrow;
		arrow.setPointCount(4);

		switch (mNextTrue)
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
		arrow.setFillColor(sf::Color(0, 255, 0));
		arrow.setScale(mBoundingBox);
		arrow.setPosition(mTopLeftCorner);
		target.draw(arrow);
	}

	if (mNextFalse != Enums::eDir::Center)
	{
		sf::ConvexShape arrow;
		arrow.setPointCount(4);

		switch (mNextFalse)
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
		arrow.setFillColor(sf::Color(255, 0, 0));
		arrow.setScale(mBoundingBox);
		arrow.setPosition(mTopLeftCorner);
		target.draw(arrow);
	}
}

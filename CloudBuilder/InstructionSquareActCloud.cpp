#include "InstructionSquareActCloud.h"
#include "CloudRobot.h"
#include "Game.h"





InstructionSquareActCloud::InstructionSquareActCloud(GameContext & gameContext) :
	InstructionSquare(gameContext, Enums::eInstruction::ActSetCloud, "Cloud Action"),
	mWantCloud(true)
{
}

InstructionSquareActCloud::InstructionSquareActCloud(GameContext & gameContext, std::string & source) :
	InstructionSquare(gameContext, Enums::eInstruction::ActSetCloud, "Cloud Action"),
	mWantCloud(true)
{
	convertFromString(source);
}

InstructionSquareActCloud::~InstructionSquareActCloud()
{
}

bool InstructionSquareActCloud::isValid()
{
	return InstructionSquare::isValid() && Enums::isValid(getRobotColor(), mGameContext);
}

bool InstructionSquareActCloud::getWantCloud()
{
	return mWantCloud;
}

void InstructionSquareActCloud::setWantCloud(bool newWant)
{
	mWantCloud = newWant;
}

std::list<Enums::eInstructionModifier> InstructionSquareActCloud::getPossibleModifications()
{
	return { Enums::eInstructionModifier::NextDir, Enums::eInstructionModifier::CloudBool, Enums::eInstructionModifier::RobotColor };
}

void InstructionSquareActCloud::applyModification(InstructionModificationData modificationData)
{
	switch (modificationData.modification)
	{
	case Enums::eInstructionModifier::NextDir: setNextDir(modificationData.dirData); break;
	case Enums::eInstructionModifier::CloudBool: setWantCloud(modificationData.boolData); break;
	case Enums::eInstructionModifier::RobotColor: setRobotColor(modificationData.colorData); break;
	default: InstructionSquare::applyModification(modificationData); break;
	}
}

std::string InstructionSquareActCloud::convertToString()
{
	return Enums::getString(getType()) + Enums::getString(getNextDir()) + Enums::getString(getWantCloud()) + Enums::getString(getRobotColor());
}

bool InstructionSquareActCloud::convertFromString(std::string & source)
{
	if (source.substr(0, 2) == Enums::getString(getType()) && source.size() >= 5)
	{
		setNextDir(Enums::getDirFromString(source[2]));
		setWantCloud(Enums::getBoolFromString(source[3]));
		setRobotColor(Enums::getColorFromString(source[4]));

		return true;
	}
	else
	{
		return false;
	}
}

bool InstructionSquareActCloud::applyInstruction(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, float progress)
{
	if (!cloudRobot.getIsWriter())
	{
		return true;
	}

	if (progress >= 1.0f)
	{
		cloudRobot.getPos().setIsCloud(mWantCloud); //TODO Animation and concurrency between robots

		//if (cloudRobot.getIsVisible())
		//{
		//	sf::Vector2f cloudPos = cloudRobot.getPos().getTopLeftCorner();
		//	sf::Vector2f cloudBox = cloudRobot.getPos().getBoundingBox();
		//	mGameContext.particleHandler.createParticle(ParticleHandler::eParticle::ParticleCloud, 1.0f, cloudPos.x + cloudBox.x / 2.0f, cloudPos.y + cloudBox.y / 2.0f, cloudBox.x / 4.0f, cloudBox.y / 4.0f);
		//}

		return true;
	}
	else
	{
		return false;
	}
}

void InstructionSquareActCloud::animateInstruction(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, float progress, float lastProgress)
{
	if (progress >= 0.2f && lastProgress < 0.2f)
	{
		mGameContext.particleHandler.createParticle(ParticleHandler::eParticle::ParticleCloud, 0.2f, cloudRobot.getPos().getTopLeftCorner().x + cloudRobot.getPos().getBoundingBox().x / 2.0f, cloudRobot.getPos().getTopLeftCorner().y + cloudRobot.getPos().getBoundingBox().y / 2.0f, cloudRobot.getPos().getBoundingBox().x / 4.0f, cloudRobot.getPos().getBoundingBox().y / 4.0f);
		mGameContext.resourceHandler.playSound(SoundHandler::eSound::SFXBlip);
	}
	if (progress >= 0.4f && lastProgress < 0.4f)
	{
		mGameContext.particleHandler.createParticle(ParticleHandler::eParticle::ParticleCloud, 0.2f, cloudRobot.getPos().getTopLeftCorner().x + cloudRobot.getPos().getBoundingBox().x / 2.0f, cloudRobot.getPos().getTopLeftCorner().y + cloudRobot.getPos().getBoundingBox().y / 2.0f, cloudRobot.getPos().getBoundingBox().x / 4.0f, cloudRobot.getPos().getBoundingBox().y / 4.0f);
		mGameContext.resourceHandler.playSound(SoundHandler::eSound::SFXBlip);
	}
	if (progress >= 0.6f && lastProgress < 0.6f)
	{
		mGameContext.particleHandler.createParticle(ParticleHandler::eParticle::ParticleCloud, 0.2f, cloudRobot.getPos().getTopLeftCorner().x + cloudRobot.getPos().getBoundingBox().x / 2.0f, cloudRobot.getPos().getTopLeftCorner().y + cloudRobot.getPos().getBoundingBox().y / 2.0f, cloudRobot.getPos().getBoundingBox().x / 4.0f, cloudRobot.getPos().getBoundingBox().y / 4.0f);
		mGameContext.resourceHandler.playSound(SoundHandler::eSound::SFXBlip);
	}
	if (progress >= 0.8f && lastProgress < 0.8f)
	{
		mGameContext.particleHandler.createParticle(ParticleHandler::eParticle::ParticleCloud, 0.2f, cloudRobot.getPos().getTopLeftCorner().x + cloudRobot.getPos().getBoundingBox().x / 2.0f, cloudRobot.getPos().getTopLeftCorner().y + cloudRobot.getPos().getBoundingBox().y / 2.0f, cloudRobot.getPos().getBoundingBox().x / 4.0f, cloudRobot.getPos().getBoundingBox().y / 4.0f);
		mGameContext.resourceHandler.playSound(SoundHandler::eSound::SFXBlip);
	}
	if (progress >= 1.0f && lastProgress < 1.0f)
	{
		mGameContext.particleHandler.createParticle(ParticleHandler::eParticle::ParticleCloud, 0.2f, cloudRobot.getPos().getTopLeftCorner().x + cloudRobot.getPos().getBoundingBox().x / 2.0f, cloudRobot.getPos().getTopLeftCorner().y + cloudRobot.getPos().getBoundingBox().y / 2.0f, cloudRobot.getPos().getBoundingBox().x / 4.0f, cloudRobot.getPos().getBoundingBox().y / 4.0f);
		mGameContext.particleHandler.createParticle(ParticleHandler::eParticle::ParticleCloud, 0.2f, cloudRobot.getPos().getTopLeftCorner().x + cloudRobot.getPos().getBoundingBox().x / 2.0f, cloudRobot.getPos().getTopLeftCorner().y + cloudRobot.getPos().getBoundingBox().y / 2.0f, cloudRobot.getPos().getBoundingBox().x / 4.0f, cloudRobot.getPos().getBoundingBox().y / 4.0f);
		mGameContext.particleHandler.createParticle(ParticleHandler::eParticle::ParticleCloud, 0.2f, cloudRobot.getPos().getTopLeftCorner().x + cloudRobot.getPos().getBoundingBox().x / 2.0f, cloudRobot.getPos().getTopLeftCorner().y + cloudRobot.getPos().getBoundingBox().y / 2.0f, cloudRobot.getPos().getBoundingBox().x / 4.0f, cloudRobot.getPos().getBoundingBox().y / 4.0f);
		mGameContext.particleHandler.createParticle(ParticleHandler::eParticle::ParticleCloud, 0.2f, cloudRobot.getPos().getTopLeftCorner().x + cloudRobot.getPos().getBoundingBox().x / 2.0f, cloudRobot.getPos().getTopLeftCorner().y + cloudRobot.getPos().getBoundingBox().y / 2.0f, cloudRobot.getPos().getBoundingBox().x / 4.0f, cloudRobot.getPos().getBoundingBox().y / 4.0f);
		mGameContext.resourceHandler.playSound(SoundHandler::eSound::SFXBlip);
	}

	float rot = fmodf(progress, 0.2f);
	rot = ((rot > 0.1f) ? (0.2f - rot) : rot) * 10.0f;
	cloudRobot.animateBody(-135.0f * rot, -135.0f * rot, 0.0f, 0.0f, true);
}

void InstructionSquareActCloud::drawInterior(sf::RenderTarget & target)
{
	sf::RectangleShape square(mBoundingBox*3.0f / 4.0f);
	square.setPosition(mTopLeftCorner + mBoundingBox / 8.0f);
	square.setFillColor(sf::Color(0, 0, 63));
	square.setOutlineThickness(1.0f);
	square.setOutlineColor(sf::Color(0, 0, 0));
	target.draw(square);

	sf::CircleShape robot(0.2f);
	robot.scale(mBoundingBox*3.0f / 4.0f);
	robot.move(sf::Vector2f(0.05f*mBoundingBox.x*3.0f / 4.0f, 0.3f*mBoundingBox.y*3.0f / 4.0f));
	robot.move(mTopLeftCorner + mBoundingBox / 8.0f);
	robot.setFillColor(Enums::getColor(mRobotColor));
	target.draw(robot);

	sf::RectangleShape cloud(sf::Vector2f(0.4f, 0.4f));
	cloud.scale(mBoundingBox*3.0f / 4.0f);
	cloud.move(sf::Vector2f(0.55f*mBoundingBox.x*3.0f / 4.0f, 0.3f*mBoundingBox.y*3.0f / 4.0f));
	cloud.move(mTopLeftCorner + mBoundingBox / 8.0f);
	if (mWantCloud)
	{
		cloud.setFillColor(sf::Color(255, 255, 255));
	}
	else
	{
		cloud.setFillColor(sf::Color(0, 0, 0));
	}
	target.draw(cloud);
}

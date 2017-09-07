#include <iostream>
#include "InstructionPlayer.h"
#include "Level.h"
#include "Game.h"



InstructionPlayer::InstructionPlayer(GameContext & gameContext, Level & level, RobotControl & robots):
	GameEntity(gameContext),
	mRobots(robots),
	mPlayerSpeed(1.0f),
	mPlayerProgress(0.0f),
	mApplyingInstruction(false),
	mIsPlaying(false),
	mPauseAtEnd(false),
	mStopAtEnd(false),
	mLevel(level)
{
	std::cout << "Creating GameEntity : InstructionPlayer." << std::endl;
}


InstructionPlayer::~InstructionPlayer()
{
}

void InstructionPlayer::activate(bool loopOnce)
{
	if (!mIsPlaying)
	{
		mRobots.processCloudRobotAttribution();
	}

	mIsPlaying = true;
	mIsPaused = false;
	//mPlayerSpeed = 10.0f; //TODO For tests purpose only

	mPauseAtEnd = loopOnce;
	mLevel.lock();

	mGameContext.resourceHandler.playMusic(true);

	std::cout << "InstructionPlayer activated." << std::endl;
}

void InstructionPlayer::deactivate()
{
	mIsPlaying = false;
	mIsPaused = false;
	mPlayerProgress = 0.0f;
	mApplyingInstruction = false;
	//mPlayerSpeed = 0.0f;
	mPauseAtEnd = false;
	mStopAtEnd = false;

	//for (auto& pair : mRobots)
	//{
	//	pair.second.resetAll();
	//}

	mLevel.unlock();
	mLevel.resetAll();

	mGameContext.resourceHandler.playMusic(false);

	std::cout << "InstructionPlayer deactivated." << std::endl;
}

void InstructionPlayer::setSpeed(float newSpeed)
{
	mPlayerSpeed = newSpeed;
}

void InstructionPlayer::setPause()
{
	mPauseAtEnd = true;
}

void InstructionPlayer::processPlayerCommand(Enums::eInstructionPlayerCommand command)
{
	switch (command)
	{
	case Enums::eInstructionPlayerCommand::CmdUnknown: break;
	case Enums::eInstructionPlayerCommand::CmdPlay: activate(false); break;
	case Enums::eInstructionPlayerCommand::CmdStop: deactivate(); break;
	case Enums::eInstructionPlayerCommand::CmdPause: setPause(); break;
	case Enums::eInstructionPlayerCommand::CmdStep: activate(true); break;
	case Enums::eInstructionPlayerCommand::CmdSpeedSlow: setSpeed(2.0f); break;
	case Enums::eInstructionPlayerCommand::CmdSpeedMedium: setSpeed(10.0f); break;
	case Enums::eInstructionPlayerCommand::CmdSpeedFast: setSpeed(50.0f); break;
	case Enums::eInstructionPlayerCommand::CmdSpeedInstant: setSpeed(-1.0f); break;
	default: break;
	}
}

Enums::eInstructionPlayerCommand InstructionPlayer::getPlayerState()
{
	if (mIsPlaying)
	{
		if (mIsPaused)
		{
			return Enums::eInstructionPlayerCommand::CmdPause;
		}
		else
		{
			return Enums::eInstructionPlayerCommand::CmdPlay;
		}
	}
	else
	{
		return Enums::eInstructionPlayerCommand::CmdStop;
	}
}

Enums::eInstructionPlayerCommand InstructionPlayer::getPlayerSpeed()
{
	if (mPlayerSpeed < 0.0f)
	{
		return Enums::eInstructionPlayerCommand::CmdSpeedInstant;
	}

	if (mPlayerSpeed < 5.0f)
	{
		return Enums::eInstructionPlayerCommand::CmdSpeedSlow;
	}

	if (mPlayerSpeed > 20.0f)
	{
		return Enums::eInstructionPlayerCommand::CmdSpeedFast;
	}

	return Enums::eInstructionPlayerCommand::CmdSpeedMedium;
}

bool InstructionPlayer::getIsPlaying()
{
	return mIsPlaying;
}

bool InstructionPlayer::getIsPaused()
{
	return mIsPaused;
}

bool InstructionPlayer::progressPlayInstant()
{
	bool allDone = true;
	mPlayerProgress = 2.0f;

	if (mApplyingInstruction)
	{
		allDone = mRobots.processCloudRobotActions(2.0f);
	}
	else
	{
		allDone = mRobots.processInstructionRobotMoves(2.0f);
	}

	if (allDone)
	{
		//if finished
		if (getCurrentResult() != Enums::eResult::Running)
		{
			//TODO
			deactivate();
			mLevel.runVerifications();
		}

		allDone = false;
		mPlayerProgress = 0.0f;
		mApplyingInstruction = !mApplyingInstruction;
		
		mRobots.resetInstructionDone(mApplyingInstruction);

		if (mStopAtEnd && mApplyingInstruction)
		{
			deactivate();
		}

		if (mPauseAtEnd && mApplyingInstruction)
		{
			mIsPaused = true;
		}

		//std::cout << "Progress done." << std::endl;
	}

	return !allDone;
}

//TODO don't apply instruction if already returned true before ?
bool InstructionPlayer::progressPlay(sf::Time dt)
{
	bool allDone = true;
	//mPlayerProgress += dt.asMilliseconds() * mPlayerSpeed / 1000.0f;
	mPlayerProgress += dt.asSeconds() * mPlayerSpeed;

	if (mApplyingInstruction)
	{
		allDone = mRobots.processCloudRobotActions(mPlayerProgress);
	}
	else
	{
		allDone = mRobots.processInstructionRobotMoves(mPlayerProgress);
	}

	if (allDone && mPlayerProgress >= 1.0f)
	{
		//if finished
		if (getCurrentResult() != Enums::eResult::Running)
		{
			//TODO
			deactivate();
			mLevel.runVerifications();
		}

		allDone = false;
		mPlayerProgress = 0.0f;
		mApplyingInstruction = !mApplyingInstruction;
		
		mRobots.resetInstructionDone(mApplyingInstruction);

		if (mStopAtEnd && mApplyingInstruction)
		{
			deactivate();
		}

		if (mPauseAtEnd && mApplyingInstruction)
		{
			mIsPaused = true;
		}

		//std::cout << "Progress done." << std::endl;
	}

	return !allDone;
}

Enums::eResult InstructionPlayer::getCurrentResult()
{
	return mRobots.getCurrentResult();
}

//void InstructionPlayer::handleEventCurrent(const sf::Event & event) //TODO For tests purposes only
//{
//	switch (event.type)
//	{
//	case sf::Event::KeyReleased:
//		if (event.key.code == sf::Keyboard::P)
//		{
//			if (mIsPlaying)
//			{
//				deactivate();
//			}
//			else
//			{
//				activate(false);
//			}
//		}
//		break;
//	}
//}

void InstructionPlayer::updateCurrent(sf::Time dt)
{
	if (!mIsPaused && mIsPlaying && mPlayerSpeed != 0.0f)
	{
		if (mPlayerSpeed < 0.0f)
		{
			progressPlayInstant();
		}
		else
		{
			progressPlay(dt);
		}
	}
}

#include "RobotControl.h"
#include "Game.h"



RobotControl::RobotControl(GameContext& gameContext, CloudCanvas& canvas, InstructionBoard& board, unsigned int nbRobots, bool isVisible):
	GameEntity(gameContext),
	mNbRobots(nbRobots),
	mIsVisible(isVisible),
	mCanvas(canvas),
	mBoard(board),
	mLastProgress(0.0f)
{
	//createRobotPairs();
	//processCloudRobotAttribution();
}


RobotControl::~RobotControl()
{
}

void RobotControl::createRobotPairs()
{
	if (mNbRobots < 1) mNbRobots = 1;
	if (mNbRobots > 4) mNbRobots = 4;

	mRobots.clear();

	for (unsigned int i = 1; i <= mNbRobots; i++)
	{
		Enums::eColor color;

		switch (i)
		{
		case 1: color = Enums::eColor::Red; break;
		case 2: color = Enums::eColor::Blue; break;
		case 3: color = Enums::eColor::Green; break;
		case 4: color = Enums::eColor::Yellow; break;
		default: color = Enums::eColor::Red; break;
		}

		mRobots.insert(std::pair<Enums::eColor, RobotPair>(color, RobotPair(mGameContext, mCanvas, mBoard, color, mIsVisible)));

		mRobots.at(color).resetAll();
	}
}

void RobotControl::startPointsUpdated()
{
	for (auto& rb : mRobots)
	{
		rb.second.startPointsUpdated();
	}
}

void RobotControl::resetAll()
{
	for (auto& pair : mRobots)
	{
		pair.second.resetAll();
	}

	processCloudRobotAttribution();

	mLastProgress = 0.0f;
}

//Check whether a CloudRobot is available for remote control
bool RobotControl::isCloudRobotAvailable(Enums::eColor robotColor)
{
	if (robotColor == Enums::eColor::NoColor)
	{
		return false;
	}

	if (Enums::isValid(robotColor, mGameContext))
	{
		if (mRobots.at(robotColor).getInstructionRobot().getIsActive())
		{
			return false;
		}
		else
		{
			unsigned int requesters = 0;

			for (auto& pair : mRobots)
			{
				if (pair.second.getInstructionRobot().getIsActive())
				{
					if (pair.second.getInstructionRobot().getPos().getRobotColor() == robotColor)
					{
						requesters++;
					}
				}
			}

			return (requesters <= 1);
		}
	}
	else
	{
		return false;
	}
}

//Here, NoColor means the associated instructionrobot do nothing.
//TODO Writable only instructions
void  RobotControl::processCloudRobotAttribution()
{
	mRobotAttributions.clear();

	for (auto& pair : mRobots)
	{
		if (pair.second.getInstructionRobot().getIsActive())
		{
			Enums::eColor wantedColor = pair.second.getInstructionRobot().getPos().getRobotColor();

			if (wantedColor == Enums::eColor::NoColor || wantedColor == pair.first)
			{
				if (pair.second.getInstructionRobot().getPos().IsWriteOnly() && !pair.second.getCloudRobot().getIsWriter())
				{
					mRobotAttributions.insert(std::pair<Enums::eColor, Enums::eColor>(pair.first, Enums::eColor::NoColor));
				}
				else
				{
					mRobotAttributions.insert(std::pair<Enums::eColor, Enums::eColor>(pair.first, pair.first));
				}
			}
			else
			{
				//The complicated case : we must check this InstructionRobot is the only one wanting access to the desired CloudRobot
				//Note that Flow instructions are truly processed in processInstructionRobotActivation and checks have no persistent effects so are always accepted
				if ((pair.second.getInstructionRobot().getPos().IsCheck() && Enums::isValid(wantedColor, mGameContext)) || isCloudRobotAvailable(wantedColor))
				{
					if (pair.second.getInstructionRobot().getPos().IsWriteOnly() && !mRobots.at(wantedColor).getCloudRobot().getIsWriter())
					{
						mRobotAttributions.insert(std::pair<Enums::eColor, Enums::eColor>(pair.first, Enums::eColor::NoColor));
					}
					else
					{
						mRobotAttributions.insert(std::pair<Enums::eColor, Enums::eColor>(pair.first, wantedColor));
					}
				}
				else
				{
					mRobotAttributions.insert(std::pair<Enums::eColor, Enums::eColor>(pair.first, Enums::eColor::NoColor));
				}
			}
		}
		else
		{
			mRobotAttributions.insert(std::pair<Enums::eColor, Enums::eColor>(pair.first, Enums::eColor::NoColor));
		}
	}
}

void RobotControl::processInstructionRobotActivation()
{
	//Step 1 : Check Pause instructions
	for (auto& pair : mRobots)
	{
		if (pair.second.getInstructionRobot().getIsActive() && (pair.second.getInstructionRobot().getPos().getType() == Enums::eInstruction::FlowPause))
		{
			Enums::eColor wantedColor = pair.second.getInstructionRobot().getPos().getRobotColor();

			if (wantedColor == Enums::eColor::NoColor)
			{
				wantedColor = pair.first;
			}

			if (Enums::isValid(wantedColor, mGameContext))
			{
				mRobots.at(wantedColor).getInstructionRobot().setIsActive(false);
			}
		}
	}

	//Step 2 : Check Resume instructions
	for (auto& pair : mRobots)
	{
		if (pair.second.getInstructionRobot().getIsActive() && (pair.second.getInstructionRobot().getPos().getType() == Enums::eInstruction::FlowResume))
		{
			Enums::eColor wantedColor = pair.second.getInstructionRobot().getPos().getRobotColor();

			if (wantedColor == Enums::eColor::NoColor)
			{
				wantedColor = pair.first;
			}

			if (Enums::isValid(wantedColor, mGameContext))
			{
				mRobots.at(wantedColor).getInstructionRobot().setIsActive(true);
			}
		}
	}

	unsigned int waitingSync = 0;

	//Step 3 : Check Sync instructions
	for (auto& pair : mRobots)
	{
		if (pair.second.getInstructionRobot().getPos().getType() == Enums::eInstruction::FlowSync)
		{
			pair.second.getInstructionRobot().setIsActive(false);
			waitingSync++;
		}
	}

	if (waitingSync >= mNbRobots)
	{
		for (auto& pair : mRobots)
		{
			pair.second.getInstructionRobot().setIsActive(true);
		}
	}
}

bool RobotControl::processInstructionRobotMoves(float progress)
{
	bool allDone = true;

	for (auto& pair : mRobots)
	{
		if (pair.second.getInstructionRobot().getIsActive())
		{
			allDone = pair.second.moveInstructionRobot(progress) && allDone;
		}
	}

	if (mIsVisible)
	{
		processAnimations(progress, false);
	}

	return allDone;
}

bool RobotControl::processCloudRobotActions(float progress)
{
	bool allDone = true;

	for (auto& pair : mRobots)
	{
		if (mRobotAttributions[pair.first] != Enums::eColor::NoColor)
		{
			if (pair.second.getInstructionRobot().getPos().IsCheck()) //Do checks first
			{
				allDone = pair.second.applyInstruction(progress, mRobots.at(mRobotAttributions[pair.first]).getCloudRobot()) && allDone;
			}
		}
	}

	for (auto& pair : mRobots)
	{
		if (mRobotAttributions[pair.first] != Enums::eColor::NoColor)
		{
			if (!pair.second.getInstructionRobot().getPos().IsCheck()) //Do non-checks second
			{
				allDone = pair.second.applyInstruction(progress, mRobots.at(mRobotAttributions[pair.first]).getCloudRobot()) && allDone;
			}
		}
	}

	setPositionChilds(mTopLeftCorner, mBoundingBox); //TODO Overkill ?

	if (mIsVisible)
	{
		processAnimations(progress, true);
	}

	return allDone;
}

void RobotControl::resetInstructionDone(bool applyInstructionNext)
{
	for (auto& pair : mRobots)
	{
		pair.second.resetInstructionDone();
	}

	if (applyInstructionNext)
	{
		processCloudRobotAttribution();
	}
	else
	{
		processInstructionRobotActivation();
	}

	mLastProgress = 0.0f;
}

void RobotControl::processAnimations(float progress, bool applyInstruction)
{
	progress = std::min(1.0f, std::max(0.0f, progress));

	if (applyInstruction)
	{
		for (auto& pair : mRobots)
		{
			if (mRobotAttributions[pair.first] != Enums::eColor::NoColor)
			{
				pair.second.animateInstruction(progress, mLastProgress, mRobots.at(mRobotAttributions[pair.first]).getCloudRobot());
			}
		}
	}
	else
	{
		for (auto& pair : mRobots)
		{
			if (!pair.second.getInstructionRobot().getIsActive())
			{
				if (progress > 0.25f && mLastProgress <= 0.25f)
				{
					mGameContext.particleHandler.createParticle(ParticleHandler::eParticle::ParticleSleep, 0.5f, pair.second.getInstructionRobot().getTopLeftCorner().x, pair.second.getInstructionRobot().getTopLeftCorner().y - pair.second.getInstructionRobot().getBoundingBox().y / 4.0f, pair.second.getInstructionRobot().getBoundingBox().x / 2.0f, pair.second.getInstructionRobot().getBoundingBox().y / 32.0f);
					mGameContext.resourceHandler.playSound(SoundHandler::eSound::SFXSleep);
				}
			}
		}
	}

	mLastProgress = progress;
}

Enums::eResult RobotControl::getCurrentResult()
{
	bool hasRejected = false;

	for (auto& pair : mRobots)
	{
		switch (pair.second.getResult())
		{
		case Enums::eResult::Accept: return Enums::eResult::Accept;
		case Enums::eResult::Refuse: hasRejected = true; break;
		case Enums::eResult::Submit: return Enums::eResult::Submit;
		default: break;
		}
	}

	if (hasRejected)
	{
		return Enums::eResult::Refuse;
	}
	else
	{
		return Enums::eResult::Running;
	}
}

void RobotControl::updateChildsVector()
{
	mChilds.clear();

	for (auto& pair : mRobots)
	{
		mChilds.push_back(pair.second);
	}
}

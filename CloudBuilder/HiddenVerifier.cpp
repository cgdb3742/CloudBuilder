#include "HiddenVerifier.h"






HiddenVerifier::HiddenVerifier(GameContext& gameContext, CloudPicture cloud, Enums::eResult wantedResult, InstructionBoard & board, unsigned int nbRobots):
	mCanvas(gameContext, cloud),
	mBoard(board),
	mReport(cloud, wantedResult),
	mSteps(0),
	mGameContext(gameContext)
{
	createRobotPairs(gameContext, nbRobots);
}

HiddenVerifier::HiddenVerifier(GameContext& gameContext, CloudPicture cloud, CloudPicture wantedCloud, InstructionBoard & board, unsigned int nbRobots) :
	mCanvas(gameContext, cloud),
	mBoard(board),
	mReport(cloud, wantedCloud),
	mSteps(0),
	mGameContext(gameContext)
{
	createRobotPairs(gameContext, nbRobots);
}

HiddenVerifier::HiddenVerifier(GameContext & gameContext, VerificationReport & report, InstructionBoard & board, unsigned int nbRobots) :
	mCanvas(gameContext, report.startingCloud),
	mBoard(board),
	mReport(report),
	mSteps(0),
	mGameContext(gameContext)
{
	createRobotPairs(gameContext, nbRobots);
}

HiddenVerifier::~HiddenVerifier()
{
}

void HiddenVerifier::createRobotPairs(GameContext & gameContext, unsigned int nb)
{
	if (nb < 1) nb = 1;
	if (nb > 4) nb = 4;

	mRobots.clear();

	for (unsigned int i = 1; i <= nb; i++)
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

		mRobots.insert(std::pair<Enums::eColor, RobotPair>(color, RobotPair(gameContext, mCanvas, mBoard, color)));

		mRobots.at(color).resetAll();
	}
}

void HiddenVerifier::resetAll()
{
	for (auto& pair : mRobots)
	{
		pair.second.resetAll();
	}

	//TODO Reset CloudBoard

	if (mReport.isValidation)
	{
		mReport = VerificationReport(mReport.startingCloud, mReport.expectedResult);
	}
	else
	{
		mReport = VerificationReport(mReport.startingCloud, mReport.expectedCloud);
	}

	mSteps = 0;
}

//TODO Expect instructions to be always complete when progress = 2.0f
void HiddenVerifier::play(unsigned int maxSteps)
{
	//unsigned int step = 0;
	bool finished = false;

	while (!finished && mSteps <= maxSteps)
	{
		mSteps++;

		for (auto& pair : mRobots)
		{
			if (pair.second.getInstructionRobot().getPos().IsCheck()) //Do checks first
			{
				pair.second.applyInstruction(2.0f);
			}
		}

		for (auto& pair : mRobots)
		{
			if (!pair.second.getInstructionRobot().getPos().IsCheck()) //Do non-checks after
			{
				pair.second.applyInstruction(2.0f);
			}
		}

		for (auto& pair : mRobots)
		{
			pair.second.resetInstructionDone();
		}

		for (auto& pair : mRobots)
		{
			pair.second.moveInstructionRobot(2.0f);
		}

		for (auto& pair : mRobots)
		{
			pair.second.resetInstructionDone();
		}

		if (getCurrentResult() != Enums::eResult::Running)
		{
			finished = true;
		}
	}

	completeReport();
}

Enums::eResult HiddenVerifier::getCurrentResult()
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

void HiddenVerifier::completeReport()
{
	//mReport.finalCloud = CloudPicture(mGameContext, mCanvas); //TODO Why does it not work ?
	mReport.finalCloud.convertFromCanvas(mCanvas);
	mReport.finalResult = getCurrentResult();
	mReport.nbSteps = mSteps;
	mReport.isComplete = true;

	if (mReport.isValidation)
	{
		mReport.isCorrectResult = (mReport.finalResult == mReport.expectedResult);
	}
	else
	{
		mReport.isCorrectResult = (mReport.finalResult == Enums::eResult::Submit && mReport.finalCloud.compare(mReport.expectedCloud));
	}
}

VerificationReport HiddenVerifier::getReport()
{
	return mReport;
}

#include "HiddenVerifier.h"
#include "Game.h"






HiddenVerifier::HiddenVerifier(GameContext& gameContext, CloudPicture cloud, Enums::eResult wantedResult, InstructionBoard & board, unsigned int nbRobots):
	mCanvas(gameContext, cloud),
	mBoard(board),
	mReport(cloud, wantedResult),
	mSteps(0),
	mGameContext(gameContext),
	mRobots(gameContext, mCanvas, board, gameContext.levelData.nbRobots, false)
{
	mRobots.createRobotPairs();
}

HiddenVerifier::HiddenVerifier(GameContext& gameContext, CloudPicture cloud, CloudPicture wantedCloud, InstructionBoard & board, unsigned int nbRobots) :
	mCanvas(gameContext, cloud),
	mBoard(board),
	mReport(cloud, wantedCloud),
	mSteps(0),
	mGameContext(gameContext),
	mRobots(gameContext, mCanvas, board, gameContext.levelData.nbRobots, false)
{
	mRobots.createRobotPairs();
}

HiddenVerifier::HiddenVerifier(GameContext & gameContext, VerificationReport & report, InstructionBoard & board, unsigned int nbRobots) :
	mCanvas(gameContext, report.startingCloud),
	mBoard(board),
	mReport(report),
	mSteps(0),
	mGameContext(gameContext),
	mRobots(gameContext, mCanvas, board, gameContext.levelData.nbRobots, false)
{
	mRobots.createRobotPairs();
}

HiddenVerifier::~HiddenVerifier()
{
}

void HiddenVerifier::resetAll()
{
	mRobots.resetAll();

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

	mRobots.processCloudRobotAttribution();

	while (!finished && mSteps <= maxSteps)
	{
		mSteps++;

		mRobots.processCloudRobotActions(2.0f);

		mRobots.resetInstructionDone(false);

		mRobots.processInstructionRobotMoves(2.0f);

		mRobots.resetInstructionDone(true);

		if (getCurrentResult() != Enums::eResult::Running)
		{
			finished = true;
		}
	}

	completeReport();
}

Enums::eResult HiddenVerifier::getCurrentResult()
{
	return mRobots.getCurrentResult();
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

#pragma once
#include <map>
#include "Enums.h"
#include "CloudCanvas.h"
#include "CloudPicture.h"
#include "InstructionBoard.h"
#include "RobotPair.h"

struct VerificationReport
{
	VerificationReport(CloudPicture cloud) : startingCloud(cloud), isValidation(true), nbSteps(0), finalCloud(cloud), isComplete(false), finalResult(Enums::eResult::Running), expectedCloud(cloud), expectedResult(Enums::eResult::Running), isCorrectResult(false) {}
	VerificationReport(CloudPicture cloud, bool wantValidation) : startingCloud(cloud), isValidation(wantValidation), nbSteps(0), finalCloud(cloud), isComplete(false), finalResult(Enums::eResult::Running), expectedCloud(cloud), expectedResult(Enums::eResult::Running), isCorrectResult(false) {}
	VerificationReport(CloudPicture cloud, Enums::eResult wantedResult) : startingCloud(cloud), isValidation(true), nbSteps(0), finalCloud(cloud), isComplete(false), finalResult(Enums::eResult::Running), expectedCloud(cloud), expectedResult(wantedResult), isCorrectResult(false) {}
	VerificationReport(CloudPicture cloud, CloudPicture wantedCloud) : startingCloud(cloud), isValidation(false), nbSteps(0), finalCloud(cloud), isComplete(false), finalResult(Enums::eResult::Running), expectedCloud(wantedCloud), expectedResult(Enums::eResult::Submit), isCorrectResult(false) {}
	//VerificationReport(CloudPicture& cloud, CloudPicture& wantedCloud) : startingCloud(cloud), isValidation(false), nbSteps(0), finalCloud(cloud), isComplete(false), finalResult(Enums::eResult::Running), expectedCloud(wantedCloud), expectedResult(Enums::eResult::Submit), isCorrectResult(false) {}
	//VerificationReport(const VerificationReport & toCopy) : startingCloud(toCopy.startingCloud), isVerification(toCopy.isVerification), nbSteps(toCopy.nbSteps), finalCloud(toCopy.finalCloud), isComplete(toCopy.isComplete), resultStatus(toCopy.resultStatus), expectedCloud(toCopy.expectedCloud), expectedResult(toCopy.expectedResult), isCorrectResult(toCopy.isCorrectResult) {}
	//VerificationReport operator=(const VerificationReport & toCopy) { startingCloud = toCopy.startingCloud; isVerification(toCopy.isVerification), nbSteps(toCopy.nbSteps), finalCloud(toCopy.finalCloud), isComplete(toCopy.isComplete), resultStatus(toCopy.resultStatus), expectedCloud(toCopy.expectedCloud), expectedResult(toCopy.expectedResult), isCorrectResult(toCopy.isCorrectResult) }

	CloudPicture startingCloud;
	bool isValidation;
	bool isComplete;

	unsigned int nbSteps;
	CloudPicture finalCloud;
	Enums::eResult finalResult;
	CloudPicture expectedCloud;
	Enums::eResult expectedResult;
	bool isCorrectResult;
};

//Note : HiddenVerifier is not meant to be drawn, updated in real time, etc... So it does implement GameEntity, yet use GameContext to reuse other classes
class HiddenVerifier
{
public:
	HiddenVerifier(GameContext& gameContext, CloudPicture cloud, Enums::eResult wantedResult, InstructionBoard& board, unsigned int nbRobots);
	HiddenVerifier(GameContext& gameContext, CloudPicture cloud, CloudPicture wantedCloud, InstructionBoard& board, unsigned int nbRobots);
	HiddenVerifier(GameContext& gameContext, VerificationReport& report, InstructionBoard& board, unsigned int nbRobots);
	~HiddenVerifier();

	void createRobotPairs(GameContext& gameContext, unsigned int nb);

	void resetAll();

	void play(unsigned int maxSteps);

	Enums::eResult getCurrentResult();

	void completeReport();

	VerificationReport getReport();

private:
	std::map<Enums::eColor, RobotPair> mRobots;
	CloudCanvas mCanvas;
	InstructionBoard& mBoard;
	VerificationReport mReport;
	unsigned int mSteps;

	GameContext& mGameContext;
};


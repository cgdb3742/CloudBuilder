#pragma once
#include "GameEntity.h"
#include "RobotPair.h"
#include "Enums.h"

class CloudCanvas;
class InstructionBoard;

class RobotControl :
	public GameEntity
{
public:
	RobotControl(GameContext& gameContext, CloudCanvas& canvas, InstructionBoard& board, unsigned int nbRobots, bool isVisible);
	~RobotControl();

	void createRobotPairs();

	void startPointsUpdated();

	void resetAll();

	bool isCloudRobotAvailable(Enums::eColor robotColor);
	void processCloudRobotAttribution();

	void processInstructionRobotActivation();

	bool processInstructionRobotMoves(float progress);
	bool processCloudRobotActions(float progress);
	void resetInstructionDone(bool applyInstructionNext);

	void processAnimations(float progress, bool applyInstruction);

	Enums::eResult getCurrentResult();
protected:
	virtual void updateChildsVector();
private:
	std::map<Enums::eColor, RobotPair> mRobots;
	std::map<Enums::eColor, Enums::eColor> mRobotAttributions;

	unsigned int mNbRobots;
	bool mIsVisible;
	CloudCanvas& mCanvas;
	InstructionBoard& mBoard;

	float mLastProgress;
};


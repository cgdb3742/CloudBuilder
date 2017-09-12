#pragma once

#include "GameEntity.h"
#include "CloudRobot.h"
#include "InstructionRobot.h"

class RobotPair :
	public GameEntity
{
public:
	RobotPair(GameContext& gameContext, CloudCanvas& canvas, InstructionBoard& board, bool isVisible);
	RobotPair(GameContext& gameContext, CloudCanvas& canvas, InstructionBoard& board, Enums::eColor color, bool isVisible);
	~RobotPair();

	//virtual void updateCurrent(sf::Time dt);
	void startPointsUpdated();

	void resetInstructionDone();
	bool applyInstruction(float progress, CloudRobot& actingRobot); //return if done
	bool moveInstructionRobot(float progress); //return if done
	void animateInstruction(float progress, float lastProgress, CloudRobot& actingRobot);
	void resetAll();

	Enums::eResult getResult();

	CloudRobot& getCloudRobot();
	InstructionRobot& getInstructionRobot();

	virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);
protected:
	virtual void updateChildsVector();
private:
	Enums::eColor mColor;
	CloudRobot mCloudRobot;
	InstructionRobot mInstructionRobot;
	CloudCanvas& mCanvas;
	InstructionBoard& mBoard;

	bool mInstructionDone;
};


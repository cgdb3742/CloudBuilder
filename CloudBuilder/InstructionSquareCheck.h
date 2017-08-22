#pragma once
#include "InstructionSquare.h"
class InstructionSquareCheck :
	public InstructionSquare
{
public:
	InstructionSquareCheck(GameContext& gameContext);
	InstructionSquareCheck(GameContext& gameContext, std::string& source);
	~InstructionSquareCheck();

	virtual Enums::eDir getNextDir(InstructionRobot& robot);
	virtual Enums::eDir getNextTrueDir();
	virtual void setNextTrueDir(Enums::eDir newDir);
	virtual Enums::eDir getNextFalseDir();
	virtual void setNextFalseDir(Enums::eDir newDir);

	virtual Enums::eDir getCheckDir();
	virtual void setCheckDir(Enums::eDir newDir);
	virtual Enums::eColor getRobotColor();
	virtual void setRobotColor(Enums::eColor newColor);

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual bool applyInstruction(CloudRobot& cloudRobot, CloudCanvas& canvas, InstructionRobot& instructionRobot, float progress);
	virtual bool performCheck(CloudRobot& cloudRobot, CloudCanvas& canvas, InstructionRobot& instructionRobot, unsigned int toChecki, unsigned int toCheckj);

	virtual void setUpNextDir(bool isLeftBorder, bool isRightBorder, bool isUpBorder, bool isDownBorder);
protected:
	InstructionSquareCheck(GameContext& gameContext, Enums::eInstruction type, std::string name);

	virtual void drawNextDir(sf::RenderTarget & target);

	Enums::eDir mNextTrue;
	Enums::eDir mNextFalse;

	Enums::eDir mCheckDir;
	Enums::eColor mRobotColor;
};

#pragma once
#include "InstructionSquare.h"
class InstructionSquareActMove :
	public InstructionSquare
{
public:
	InstructionSquareActMove();
	explicit InstructionSquareActMove(std::string& source);
	~InstructionSquareActMove();

	Enums::eDir getToMove();
	void setToMove(Enums::eDir newDir);
	Enums::eColor getRobotColor();
	void setRobotColor(Enums::eColor newColor);

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::string convertToString();
	virtual bool convertFromString(std::string& source);

	virtual bool applyInstruction(CloudRobot& cloudRobot, CloudCanvas& canvas, InstructionRobot& instructionRobot, float progress);

	virtual void drawInterior(sf::RenderTarget & target);
private:
	Enums::eDir mToMove;
	Enums::eColor mRobotColor;
};


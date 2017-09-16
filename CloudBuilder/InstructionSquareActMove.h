#pragma once
#include "InstructionSquare.h"
class InstructionSquareActMove :
	public InstructionSquare
{
public:
	InstructionSquareActMove(GameContext& gameContext);
	InstructionSquareActMove(GameContext& gameContext, std::wstring& source);
	~InstructionSquareActMove();

	virtual bool isValid();

	Enums::eDir getToMove();
	void setToMove(Enums::eDir newDir);

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::wstring convertToString();
	virtual bool convertFromString(std::wstring& source);

	virtual bool applyInstruction(CloudRobot& cloudRobot, CloudCanvas& canvas, InstructionRobot& instructionRobot, float progress);

	virtual void animateInstruction(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, float progress, float lastProgress);

	virtual void drawInterior(sf::RenderTarget & target);
private:
	Enums::eDir mToMove;
};


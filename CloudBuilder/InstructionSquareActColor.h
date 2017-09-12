#pragma once
#include "InstructionSquare.h"
class InstructionSquareActColor :
	public InstructionSquare
{
public:
	InstructionSquareActColor(GameContext& gameContext);
	InstructionSquareActColor(GameContext& gameContext, std::string& source);
	~InstructionSquareActColor();

	virtual bool isValid();

	Enums::eColor getCloudColor();
	void setCloudColor(Enums::eColor newColor);

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::string convertToString();
	virtual bool convertFromString(std::string& source);

	virtual bool applyInstruction(CloudRobot& cloudRobot, CloudCanvas& canvas, InstructionRobot& instructionRobot, float progress);

	virtual void animateInstruction(CloudRobot& cloudRobot, CloudCanvas& canvas, InstructionRobot& instructionRobot, float progress, float lastProgress);

	virtual void drawInterior(sf::RenderTarget & target);
private:
	Enums::eColor mCloudColor;
};


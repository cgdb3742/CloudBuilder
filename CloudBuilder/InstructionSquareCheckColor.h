#pragma once
#include "InstructionSquareCheck.h"
class InstructionSquareCheckColor :
	public InstructionSquareCheck
{
public:
	InstructionSquareCheckColor(GameContext& gameContext);
	InstructionSquareCheckColor(GameContext& gameContext, std::string& source);
	~InstructionSquareCheckColor();

	virtual Enums::eColor getCloudColor();
	virtual void setCloudColor(Enums::eColor newColor);

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::string convertToString();
	virtual bool convertFromString(std::string& source);

	virtual bool performCheck(CloudRobot& cloudRobot, CloudCanvas& canvas, InstructionRobot& instructionRobot, unsigned int toChecki, unsigned int toCheckj);
protected:
	virtual void drawInterior(sf::RenderTarget & target);
private:
	Enums::eColor mCloudColor;
};


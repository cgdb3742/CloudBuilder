#pragma once
#include "InstructionSquareCheck.h"
class InstructionSquareCheckColor :
	public InstructionSquareCheck
{
public:
	InstructionSquareCheckColor(GameContext& gameContext);
	InstructionSquareCheckColor(GameContext& gameContext, std::wstring& source);
	~InstructionSquareCheckColor();

	virtual Enums::eColor getCloudColor();
	virtual void setCloudColor(Enums::eColor newColor);

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::wstring convertToString();
	virtual bool convertFromString(std::wstring& source);

	virtual bool performCheck(CloudRobot& cloudRobot, CloudCanvas& canvas, InstructionRobot& instructionRobot, unsigned int toChecki, unsigned int toCheckj);
protected:
	virtual void drawInterior(sf::RenderTarget & target);
private:
	Enums::eColor mCloudColor;
};

